/* ========================================================================= */
/*!
 *
 * \file            Serializer.tpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines helper functions for serializing Barrage objects (registered
 * through RTTR).
 * 
 * Source for some of the ideas used for this serializer: 
 * https://0x00000000.dev/reflection-serializer/
 * 
*/
/* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================

#include <stdafx.h>
#include <string>
#include "Serializer.hpp"

#include <iostream>
#include <unordered_map>
#include <string_view>
#include <string>

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

  const std::string_view KeyHeader = "Key";
  const std::string_view ValueHeader = "Value";
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
      value.SetString(rapidjson::GenericStringRef<char>(text.c_str()), allocator);
    }

    return value;
  }

  void DeserializePrimitive(rttr::variant& property, const rapidjson::Value& value, rttr::type propertyType)
  {
    // Do a massive branching statement until we can figure out a better
    // way of doing this.
    /* rttr::type propertyType = property.get_type(); */

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
    // Establish the JSON value to serialize.
    rapidjson::Value value(rapidjson::kNullType);

    // The object being serialized as an unwrapped object.
    rttr::variant unwrappedObject = object;
    rttr::type type = object.get_type();

    if (!type)
    {
      BREAKPOINT();
      return value;
    }

    // We care about the contents of all wrapper types.
    if (type.is_wrapper())
    {
      type = type.get_wrapped_type();
      unwrappedObject = unwrappedObject.extract_wrapped_value();
    }

    // Handle array-like types.
    if (type.is_sequential_container())
    {
      const rttr::variant_sequential_view& asArray = unwrappedObject.create_sequential_view();
      // Make this value an array.
      value.SetArray();
      // Go through all the possible values of this.
      for (auto& element : asArray)
      {
        rapidjson::Value elemValue = Serialize(element, allocator);
        value.PushBack(elemValue, allocator);
      }
    }
    // Handle map types.
    else if (type.is_associative_container())
    {
      const rttr::variant_associative_view& asMap = unwrappedObject.create_associative_view();
      // Make this value an array of objects, weirdly enough.
      value.SetArray();
      // Go through all the possible values of this.
      for (auto& element : asMap)
      {
        const rttr::variant& objectKey = element.first;
        const rttr::variant& objectValue = element.second;
        rapidjson::Value keyContents = Serialize(objectKey, allocator);
        rapidjson::Value valueContents = Serialize(objectValue, allocator);
        rapidjson::Value entry(rapidjson::kObjectType);
        entry.AddMember(rapidjson::GenericStringRef<char>(KeyHeader.data()), keyContents, allocator);
        entry.AddMember(rapidjson::GenericStringRef<char>(ValueHeader.data()), valueContents, allocator);
        value.PushBack(entry, allocator);
      }
    }
    // Handle primitive types (including strings).
    else if (IsRapidJsonPrimitive(type))
    {
      value = SerializePrimitive(unwrappedObject, allocator);
    }
    // Handle classes.
    else if (type.is_class())
    {
      value.SetObject();
      // Go through all properties and attempt to serialize them.
      const rttr::array_range<rttr::property> properties = type.get_properties();
      for (const auto property : properties)
      {
        rapidjson::Value translatedValue;
        rttr::variant propertyAsValue = property.get_value(unwrappedObject);
        // Serialize the variant's properties.
        translatedValue = Serialize(propertyAsValue, allocator);
        // Set whatever value we got from RTTR to RapidJSON.
        const std::string_view properyName = property.get_name().data();
        value.AddMember(rapidjson::GenericStringRef<char>(properyName.data()), translatedValue, allocator);
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

  void Deserialize(rttr::variant& object, const rapidjson::Value& data, rttr::type type)
  {
    // The object being serialized as an unwrapped object.
    rttr::variant unwrappedObject = object;

    if (!type)
    {
      BREAKPOINT();
      return;
    }

    // We care about the contents of all wrapper types.
    if (type.is_wrapper())
    {
      type = type.get_wrapped_type();
      unwrappedObject = unwrappedObject.extract_wrapped_value();
    }

    // Handle array-like objects.
    if (type.is_sequential_container())
    {
      // The array from the JSON data.
      const rapidjson::GenericArray<true, rapidjson::Value> dataAsArray = data.GetArray();
      // The propery we are constructing.
      rttr::variant_sequential_view objectAsArray = object.create_sequential_view();

      // Get the size of the array.
      size_t arraySize = dataAsArray.Size();
      objectAsArray.set_size(arraySize);
      // Sometimes, the array may not resize, and therefore we need to make sure
      // we get an accurate size for this array or we go out of bounds.
      arraySize = objectAsArray.get_size();

      // Search through all the elements of the array data and copy them over to our data.
      for (uint32_t i = 0; i < arraySize; ++i)
      {
        // Deserialize each member of this array and then slot them into
        // our newly created array.
        rttr::variant arrayElement = objectAsArray.get_value(i);
        // Get the contents of the wrapper if that's what we got.
        Deserialize(arrayElement, dataAsArray[i], objectAsArray.get_value_type());
        objectAsArray.set_value(i, arrayElement);
      }
    }
    // Handle map types.
    else if (type.is_associative_container())
    {
      // The array from the JSON data.
      const rapidjson::GenericArray<true, rapidjson::Value> dataAsArray = data.GetArray();
      const size_t arraySize = dataAsArray.Size();
      // The property as an associative container.
      rttr::variant_associative_view objectAsMap = object.create_associative_view();
      const rttr::type keyType = objectAsMap.get_key_type();
      const rttr::type valueType = objectAsMap.get_value_type();
      
      for (uint32_t i = 0; i < arraySize; ++i)
      {
        // Deserialize each member of this map.
        using rapidjson::CrtAllocator;
        using rapidjson::MemoryPoolAllocator;
        using Iterator = const rapidjson::GenericMemberIterator < true, rapidjson::UTF8<>, MemoryPoolAllocator<CrtAllocator> >;

        const rapidjson::Value& entry = dataAsArray[i];
        Iterator keyContentsIter = entry.FindMember(KeyHeader.data());
        Iterator valueContentsIter = entry.FindMember(ValueHeader.data());
        if (keyContentsIter != entry.MemberEnd() && valueContentsIter != entry.MemberEnd())
        {
          const rapidjson::Value& keyContents = keyContentsIter->value;
          const rapidjson::Value& valueContents = valueContentsIter->value;

          rttr::variant key, value;
          value = valueType.create();
          key = keyType.create();

          Deserialize(key, keyContents, keyType);
          Deserialize(value, valueContents, valueType);

          auto success = objectAsMap.insert(key, value);
          (void)success;
          assert(success.second);
        }
      }
    }
    // Handle primitive types.
    else if (IsRapidJsonPrimitive(type))
    {
      DeserializePrimitive(object, data, type);
    }
    // Handle classes.
    else if (type.is_class())
    {
      // Go through all properties and attempt to serialize them.
      rttr::array_range<rttr::property> properties = type.get_properties();
      assert(properties.size() > 0);
      for (auto property : properties)
      {
        using rapidjson::CrtAllocator;
        using rapidjson::MemoryPoolAllocator;
        using Iterator = const rapidjson::GenericMemberIterator < true, rapidjson::UTF8<>, MemoryPoolAllocator<CrtAllocator> >;

        const std::string_view propertyName = property.get_name().data();
        const Iterator memberIter = data.FindMember(propertyName.data());

        if (memberIter != data.MemberEnd())
        {
          const rapidjson::Value& propertyData = memberIter->value;
          rttr::variant propertyVariant = property.get_value(object);
          rttr::type propertyType = property.get_type();

          Deserialize(propertyVariant, propertyData, propertyType);
          bool success = property.set_value(object, propertyVariant);
          assert(success);
          UNREFERENCED(success);
        }
      }
    }
    // Uhhhh... we shouldn't be here.
    else
    {
      BREAKPOINT();
    }
  }
}
