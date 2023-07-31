/* ======================================================================== */
/*!
 * \file            SpawnRule.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A spawn rule modifies the initial values of a newly spawned object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRule_BARRAGE_T
#define SpawnRule_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  SpawnRuleT<T>::SpawnRuleT(const std::string& name) : SpawnRule(name), data_()
  {
  }
  
  template <typename T>
  rttr::variant SpawnRuleT<T>::GetRTTRValue()
  {
    rttr::variant value = data_;

    return value;
  }

  template <typename T>
  void SpawnRuleT<T>::SetRTTRValue(const rttr::variant& value)
  {
    if (value.get_type() != rttr::type::get<T>())
    {
      return;
    }

    data_ = value.get_value<T>();
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRule_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////