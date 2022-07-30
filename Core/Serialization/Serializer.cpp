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

#include <unordered_map>
#include <iostream>

#include <rttr/type.h>
#include <rttr/property.h>
#include <rttr/variant.h>
#include <rapidjson/document.h>


namespace
{
  bool IsRapidJsonPrimitive(const rttr::type& type)
  {
    return !type.is_class() || type == rttr::type::get<std::string>();
  }
}
namespace Barrage
{

  rapidjson::Value SerializePrimitive(const rttr::variant& property,
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
    rapidjson::Value value;
    rttr::variant propertyVariant = property;
    rttr::type propertyType = property.get_type();

    // We care about the contents of all wrapper types.
    if (propertyType.is_wrapper())
    {
      propertyType = propertyType.get_wrapped_type();
      propertyVariant = propertyVariant.extract_wrapped_value();
    }

    // I genuinely don't know how to do this any other way
    // because of the templating.
    if (propertyType == rttr::type::get<int>())
    {
      value = propertyVariant.get_value<int>();
    }
    else if (propertyType == rttr::type::get<bool>())
    {
      value = propertyVariant.get_value<bool>();
    }
    else if (propertyType == rttr::type::get<unsigned int>())
    {
      value = propertyVariant.get_value<unsigned int>();
    }
    else if (propertyType == rttr::type::get<float>())
    {
      value = propertyVariant.get_value<float>();
    }
    else if (propertyType == rttr::type::get<double>())
    {
      value = propertyVariant.get_value<double>();
    }
    else if (propertyType == rttr::type::get<char>())
    {
      value = propertyVariant.get_value<char>();
    }
    else if (propertyType == rttr::type::get<unsigned char>())
    {
      value = propertyVariant.get_value<unsigned char>();
    }
    else if (propertyType == rttr::type::get<long>())
    {
      value = propertyVariant.get_value<long>();
    }
    else if (propertyType == rttr::type::get<size_t>())
    {
      value = propertyVariant.get_value<size_t>();
    }
    else if (propertyType == rttr::type::get<std::string>())
    {
      const std::string text = propertyVariant.get_value<std::string>();
      value.SetString(rapidjson::GenericStringRef(text.c_str()), allocator);
    }

    return value;
  }

  void DeserializePrimitive(rttr::variant& property, const rapidjson::Value& value)
  {
    // Do a massive branching statement until we can figure out a better
    // way of doing this.
    rttr::type propertyType = property.get_type();

    // We care about the contents of all wrapper types.
    if (propertyType.is_wrapper())
    {
      propertyType = propertyType.get_wrapped_type();
    }

    if (propertyType == rttr::type::get<int>())
    {
      assert(value.IsInt());
      property = value.GetInt();
    }
    else if (propertyType == rttr::type::get<unsigned int>())
    {
      // Manually convert integers to unsigned integers
      // should we need to.
      assert(value.IsUint());
      property = value.GetUint();
    }
    else if (propertyType == rttr::type::get<bool>())
    {
      assert(value.IsBool());
      property = value.GetBool();
    }
    else if (propertyType == rttr::type::get<float>())
    {
      assert(value.IsFloat());
      property = value.GetFloat();
    }
    else if (propertyType == rttr::type::get<double>())
    {
      // Manually convert the single precision floating point
      // value to a double precision type... shouldn't be
      // a bad conversion.
      assert(value.IsDouble());
      property = value.GetDouble();
    }
    else if (propertyType == rttr::type::get<long>())
    {
      property = value.Get<long>();
    }
    else if (propertyType == rttr::type::get<size_t>())
    {
      property = value.Get<size_t>();
    }
    else if (propertyType == rttr::type::get<std::string>())
    {
      property = std::string(value.GetString());
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
    rapidjson::Value value;// (rapidjson::kObjectType);
    /*
    const std::string_view className = object.get_type().get_name().data();
    const rttr::type type = rttr::type::get_by_name(className.data());
    */
    const rttr::type type = object.get_type();
    // Handle array-like types.
    if (type.is_sequential_container())
    {
      const rttr::variant_sequential_view& asArray = object.create_sequential_view();
      // Make this value an array.
      value.SetArray();
      // Go through all the possible values of this.
      for (auto& element : asArray)
      {
        rapidjson::Value elemValue = SerializePrimitive(element, allocator);
        value.PushBack(elemValue, allocator);
      }
    }
    // Handle primitive types (including strings).
    else if (IsRapidJsonPrimitive(type))
    {
      value = SerializePrimitive(object, allocator);
    }
    // Handle classes.
    else if (type.is_class())
    {
      value.SetObject();
      // Go through all properties and attempt to serialize them.
      const rttr::array_range properties = type.get_properties();
      for (const auto property : properties)
      {
        rapidjson::Value translatedValue;
        rttr::variant propertyAsValue = property.get_value(object);
        rttr::type propertyType = property.get_type();
        // Serialize the variant's properties.
        translatedValue = Serialize(propertyAsValue, allocator);
        // Set whatever value we got from RTTR to RapidJSON.
        const std::string_view properyName = property.get_name().data();
        value.AddMember(rapidjson::GenericStringRef(properyName.data()), translatedValue, allocator);
      }
    }
    // We really shouldn't be here...
    else
    {
      BREAKPOINT();
    }
    // Return whatever JSON value we constructed.
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
        const rttr::type propertyType = property.get_type();
        rttr::variant propertyVariant = property.get_value(object);

        if (memberIter != data.MemberEnd())
        {
          const rapidjson::Value& propertyData = memberIter->value;
          if (propertyType.is_sequential_container())
          {
            // The array from the JSON data.
            const rapidjson::GenericArray dataAsArray = propertyData.GetArray();
            const size_t arraySize = dataAsArray.Size();
            // The propery we are constructing.
            rttr::variant_sequential_view propertyAsArray = propertyVariant.create_sequential_view();
            propertyAsArray.set_size(arraySize);
            // Search through all the elements of the array data and copy them over to our data.
            for (size_t i = 0; i < arraySize; ++i)
            {
              // Deserialize each member of this array and then slot them into
              // our newly created array.
              rttr::variant arrayElement = propertyAsArray.get_value(i);
              rttr::type arrayElementType = arrayElement.get_type();
              // Get the contents of the wrapper if that's what we got.
              DeserializePrimitive(arrayElement, dataAsArray[i]);
              propertyAsArray.set_value(i, arrayElement);
            }
            //propertyVariant = propertyAsArray;
          }
          else if(IsRapidJsonPrimitive(propertyType))
          {
            DeserializePrimitive(propertyVariant, propertyData);
          }
          else
          {
            Deserialize(propertyVariant, propertyData);
            // Set the property after reading.
          }
          property.set_value(object, propertyVariant);
        }
      }
    }
  }
}
