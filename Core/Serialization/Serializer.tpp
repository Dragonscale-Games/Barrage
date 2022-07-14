/* ========================================================================= */
/*!
 *
 * \file            Serializer.tpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines helper functions for serializing Barrage objects (registered
 * through RTTR).
*/
/* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================

//#include <stdafx.hpp>
#include <rttr/type.h>
#include <rttr/property.h>
#include <rapidjson/document.h>
#include <unordered_map>
#include <iostream>

namespace Barrage
{
  rapidjson::Value Serialize(const rttr::variant& object, const rttr::property& property)
  {
    /*
    const static std::unordered_map<rttr::type, rapidjson::Type> typeTranslator =
    {
      // A ton of number types.
      { rttr::type::get<unsigned char>, rapidjson::kNumberType },
    };
    */

    // The metadata about the property coming from RTTR.
    const rttr::variant variant = property.get_value(object);
    const rttr::type variantType = property.get_type();
    // The converted property as a RapidJSON value.
    rapidjson::Value value;
    
    // I genuinely don't know how to do this any other way
    // because of the templating.
    if (variantType == rttr::type::get<int>())
    {
      value = variant.get_value<int>();
    }
    else if (variantType == rttr::type::get<bool>())
    {
      value = variant.get_value<bool>();
    }
    else if (variantType == rttr::type::get<unsigned int>())
    {
      value = variant.get_value<unsigned int>();
    }
    else if (variantType == rttr::type::get<float>())
    {
      value = variant.get_value<float>();
    }
    else if (variantType == rttr::type::get<double>())
    {
      value = variant.get_value<double>();
    }
    else if (variantType == rttr::type::get<long>())
    {
      value = variant.get_value<long>();
    }
    else if (variantType == rttr::type::get<size_t>())
    {
      value = variant.get_value<size_t>();
    }

    return value;
  }

  rapidjson::Value Serialize(const rttr::variant& object,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    // Get the component through RTTR if possible.
    rapidjson::Value value(rapidjson::kObjectType);
    const std::string_view className = object.get_type().get_name().data();
    const std::string_view trimmedClassName = className.substr(className.find_last_of("::") + 1);
    const rttr::type type = rttr::type::get_by_name(trimmedClassName.data());
    if (type)
    {
      // Go through all properties and attempt to serialize them.
      rttr::array_range properties = type.get_properties();
      for (const auto property : properties)
      {
        // If the class is a type then we call this function recursively.
        // Otherwise, we get whatever base type we got.
        rapidjson::Value propertyValue;
        if (property.get_type().is_class())
        {
          propertyValue = Serialize(property.get_value(object), allocator);
        }
        else
        {
          propertyValue = Serialize(object, property);
        }
        // Set whatever value we got from RTTR to RapidJSON.
        const std::string_view properyName = property.get_name().data();
        value.AddMember(rapidjson::GenericStringRef(properyName.data()), propertyValue, allocator);
      }
    }

    return value;
  }
}
