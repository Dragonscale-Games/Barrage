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

namespace Barrage
{
  template <class T>
  void Deserialize(T& object, const rapidjson::Value& data) noexcept(false)
  {
    rttr::variant objectVariant(object);
    Deserialize(objectVariant, data, objectVariant.get_type());

    if (objectVariant.is_type<T>())
    {
      object = objectVariant.get_value<T>();
    }
  }

  template <class T>
  void Deserialize(T& object, const rapidjson::Value& data, const rttr::type& type) noexcept(false)
  {
    rttr::variant objectVariant(object);
    if (objectVariant.can_convert(type))
    {
      objectVariant.convert(type);
      Deserialize(objectVariant, data, type);

      if (objectVariant.is_type<T>())
      {
        object = objectVariant.get_value<T>();
      }
    }
  }
}
