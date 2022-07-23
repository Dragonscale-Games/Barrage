/* ========================================================================= */
/*!
 *
 * \file            Serializer.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines helper functions for serializing Barrage objects (registered
 * through RTTR).
 */
 /* ========================================================================= */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Serializer_MODULE_H
#define Serializer_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
#include <rttr/registration.h>

namespace Barrage
{
  /*************************************************************************/
  /*!
    \brief
    \param object
      The object being serialized. It must be registered through
      rttr.
    \tparam T
      The type of object being serialized.
    \returns
      A rapidjson value representing the serialized object.
  */
  /*************************************************************************/
  rapidjson::Value Serialize(const rttr::variant& object,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);
  /*************************************************************************/
  /*!
    \brief
      Deserializes an object given the JSON data for it.
    \param object
      The object to deserialize from JSON data.
    \param data
      The object representing the JSON data being read.
  */
  /*************************************************************************/
  void Deserialize(rttr::variant& object, const rapidjson::Value& data);
  /*************************************************************************/
  /*!
    \brief
      A helper class that sets up some initial conditions for the
      main `Deserialize` function to work.
    \param object
      The object to being written to with JSON data.
    \param data
      The object representing the JSON data being read.
    \tparam T
      The type of object being deserialized.
  */
  /*************************************************************************/
  template <class T>
  void Deserialize(T& object, const rapidjson::Value& data);
}

#include "Serializer.tpp"
#endif // Serializer_MODULE_H
