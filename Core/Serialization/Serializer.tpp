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
}
