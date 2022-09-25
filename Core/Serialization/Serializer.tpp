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

namespace Barrage
{
  template <class T>
  void Deserialize(T& object, const rapidjson::Value& data)
  {
    rttr::variant objectVariant(object);
    Deserialize(objectVariant, data, objectVariant.get_type());

    object = objectVariant.get_value<T>();
  }

  template <class T>
  void Deserialize(T& object, const rapidjson::Value& data, const rttr::type& type)
  {
    rttr::variant objectVariant(object);
    if (objectVariant.can_convert(type))
    {
      objectVariant.convert(type);
      Deserialize(objectVariant, data, type);
      object = objectVariant.get_value<T>();
    }
  }
}
