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

  template <typename T, typename A>
  SpawnRuleTA<T,A>::SpawnRuleTA(const std::string& name) : SpawnRuleWithArray(name), data_(), dataArray_()
  {
  }

  template <typename T, typename A>
  rttr::variant SpawnRuleTA<T, A>::GetRTTRValue()
  {
    rttr::variant value = data_;

    return value;
  }

  template <typename T, typename A>
  void SpawnRuleTA<T, A>::SetRTTRValue(const rttr::variant& value)
  {
    if (value.get_type() != rttr::type::get<T>())
    {
      return;
    }

    data_ = value.get_value<T>();
  }

  template <typename T, typename A>
  void SpawnRuleTA<T, A>::SetCapacity(unsigned capacity)
  {
    dataArray_.SetCapacity(capacity);
  }

  template <typename T, typename A>
  void SpawnRuleTA<T, A>::HandleDestructions(const bool* destructionArray, unsigned deadBeginIndex, unsigned aliveEndIndex)
  {
    unsigned numAliveObjects = dataArray_.HandleDestructions(destructionArray, deadBeginIndex, aliveEndIndex);

    for (unsigned i = numAliveObjects; i < aliveEndIndex; ++i)
    {
      dataArray_.Data(i) = A();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRule_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////