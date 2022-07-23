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

#include <stdafx.h>
#include "Serializer.hpp"

#include <rttr/type.h>
#include <rttr/property.h>
#include <rapidjson/document.h>
#include <unordered_map>
#include <iostream>

namespace
{
  bool CanRapidJsonHandle(const rttr::property& property)
  {
    rttr::type type = property.get_type();
    return !type.is_class() || type == rttr::type::get<std::string>();
  }
}
namespace Barrage
{

  rapidjson::Value Serialize(const rttr::variant& object, const rttr::property& property, 
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
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
    else if (variantType == rttr::type::get<std::string>())
    {
      const std::string text = variant.get_value<std::string>();
      value.SetString(rapidjson::GenericStringRef(text.c_str()), allocator);
    }

    return value;
  }

  void Deserialize(rttr::variant& object, const rttr::property& property, const rapidjson::Value& value)
  {
    // Do a massive branching statement until we can figure out a better
    // way of doing this.
    rttr::type propertyType = property.get_type();
    if (propertyType == rttr::type::get<int>())
    {
      assert(value.IsInt());
      property.set_value(object, value.GetInt());
    }
    else if (propertyType == rttr::type::get<unsigned int>())
    {
      // Manually convert integers to unsigned integers
      // should we need to.
      assert(value.IsUint());
      property.set_value(object, value.GetUint());
    }
    else if (propertyType == rttr::type::get<bool>())
    {
      assert(value.IsBool());
      property.set_value(object, value.GetBool());
    }
    else if (propertyType == rttr::type::get<float>())
    {
      assert(value.IsFloat());
      property.set_value(object, value.GetFloat());
    }
    else if (propertyType == rttr::type::get<double>())
    {
      // Manually convert the single precision floating point
      // value to a double precision type... shouldn't be
      // a bad conversion.
      assert(value.IsDouble());
      property.set_value(object, value.GetDouble());
    }
    else if (propertyType == rttr::type::get<long>())
    {
      property.set_value(object, value.Get<long>());
    }
    else if (propertyType == rttr::type::get<size_t>())
    {
      property.set_value(object, value.Get<size_t>());
    }
    else if (propertyType == rttr::type::get<std::string>())
    {
      property.set_value(object, std::string(value.GetString()));
    }
    else
    {
      // We, ideally, never reach this part of execution.
      BREAKPOINT();
    }
  }

  rapidjson::Value Serialize(const rttr::variant& object,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    // Get the component through RTTR if possible.
    rapidjson::Value value(rapidjson::kObjectType);
    const std::string_view className = object.get_type().get_name().data();
    const rttr::type type = rttr::type::get_by_name(className.data());
    if (type)
    {
      // Go through all properties and attempt to serialize them.
      const rttr::array_range properties = type.get_properties();
      for (const auto property : properties)
      {
        // If the class is a type then we call this function recursively.
        // Otherwise, we get whatever base type we got.
        rapidjson::Value propertyValue;
        if (CanRapidJsonHandle(property))
        {
          propertyValue = Serialize(object, property, allocator);
        }
        else
        {
          propertyValue = Serialize(property.get_value(object), allocator);
        }
        // Set whatever value we got from RTTR to RapidJSON.
        const std::string_view properyName = property.get_name().data();
        value.AddMember(rapidjson::GenericStringRef(properyName.data()), propertyValue, allocator);
      }
    }

    return value;
  }

  void Deserialize(rttr::variant& object, const rapidjson::Value& data)
  {
    const std::string_view className = object.get_type().get_name().data();
    const rttr::type type = rttr::type::get_by_name(className.data());
    if (type)
    {
      // Go through all properties and attempt to serialize them.
      rttr::array_range properties = type.get_properties();
      for (auto property : properties)
      {
        const std::string_view propertyName = property.get_name().data();
        const rapidjson::GenericMemberIterator memberIter = data.FindMember(propertyName.data());
        if (memberIter != data.MemberEnd())
        {
          const rapidjson::Value& propertyData = memberIter->value;
          if(CanRapidJsonHandle(property))
          {
            Deserialize(object, property, propertyData);
          }
          else
          {
            rttr::variant propertyVariant = property.get_value(object);
            Deserialize(propertyVariant, propertyData);
            // Set the property after reading.
            property.set_value(object, propertyVariant);
          }
        }
      }
    }
  }
}
