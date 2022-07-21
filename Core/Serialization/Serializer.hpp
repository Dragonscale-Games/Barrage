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
  /*
  template <typename T>
  rapidjson::Value Serialize(
    const T& object,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator) noexcept(false);
  */
  rapidjson::Value Serialize(const rttr::variant& object,
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);
  /*************************************************************************/
  /*************************************************************************/
  //void Deserialize(rttr::variant object, const rapidjson::Value& data);
  void Deserialize(rttr::variant& object, const rapidjson::Value& data);
  
  template <class T>
  void Deserialize(T& object, const rapidjson::Value& data)
  {
    rttr::variant objectVariant(object);
    Deserialize(objectVariant, data);

    object = objectVariant.get_value<T>();
  }
}
#endif // Serializer_MODULE_H
