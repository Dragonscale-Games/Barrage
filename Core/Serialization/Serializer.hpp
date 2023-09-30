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
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
#include <rttr/registration.h>

namespace Barrage
{
  /*************************************************************************/
  /*!
    \brief
      Serializes an RTTR object into a rapidjson value.
    \param object
      The object being serialized. It must be registered through
      rttr.
    \param allocator
      RapidJson allocator being used.
    \return
      A rapidjson value representing the serialized object.
  */
  /*************************************************************************/
  rapidjson::Value Serialize(const rttr::variant& object,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

  /*************************************************************************/
  /*!
    \brief
      Deserializes a rapidjson value into an RTTR object.
    \param object
      The object to deserialize from JSON data.
    \param data
      The object representing the JSON data being read.
  */
  /*************************************************************************/
  void Deserialize(rttr::variant& object, const rapidjson::Value& data, rttr::type type) noexcept(false);
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
  void Deserialize(T& object, const rapidjson::Value& data) noexcept(false);
  /*************************************************************************/
  /*************************************************************************/
  template <class T>
  void Deserialize(T& object, const rapidjson::Value& data, const rttr::type& type) noexcept(false);
}

#include "Serializer.tpp"
#endif // Serializer_MODULE_H
