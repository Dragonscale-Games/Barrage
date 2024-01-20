/* ======================================================================== */
/*!
 * \file            BehaviorNode.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorNode_BARRAGE_T
#define BehaviorNode_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  BehaviorNodeT<T>::BehaviorNodeT(
    const std::string& name, 
    unsigned maxChildren
  ) : 
    BehaviorNode(name, maxChildren), 
    data_()
  {
  }

  template <typename T>
  std::shared_ptr<BehaviorNode> BehaviorNodeT<T>::Clone() const
  {
    return std::make_shared<BehaviorNodeT<T>>(*this);
  }

  template <typename T>
  rttr::variant BehaviorNodeT<T>::GetRTTRValue()
  {
    rttr::variant value = data_;

    return value;
  }

  template <typename T>
  void BehaviorNodeT<T>::SetRTTRValue(const rttr::variant& value)
  {
    if (value.get_type() != rttr::type::get<T>())
    {
      return;
    }

    data_ = value.get_value<T>();
  }

  template <typename T, typename A>
  BehaviorNodeTA<T, A>::BehaviorNodeTA(
    const std::string& name, 
    unsigned maxChildren
  ) : 
    BehaviorNodeWithArray(name, maxChildren),
    data_(), 
    dataArray_()
  {
  }

  template <typename T, typename A>
  std::shared_ptr<BehaviorNode> BehaviorNodeTA<T, A>::Clone() const
  {
    return std::make_shared<BehaviorNodeTA<T, A>>(*this);
  }

  template <typename T, typename A>
  rttr::variant BehaviorNodeTA<T, A>::GetRTTRValue()
  {
    rttr::variant value = data_;

    return value;
  }

  template <typename T, typename A>
  void BehaviorNodeTA<T, A>::SetRTTRValue(const rttr::variant& value)
  {
    if (value.get_type() != rttr::type::get<T>())
    {
      return;
    }

    data_ = value.get_value<T>();
  }

  template <typename T, typename A>
  void BehaviorNodeTA<T, A>::SetCapacity(unsigned capacity)
  {
    dataArray_.SetCapacity(capacity);
  }

  template <typename T, typename A>
  void BehaviorNodeTA<T, A>::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    unsigned numAliveObjects = dataArray_.HandleDestructions(destructionArray, writeIndex, endIndex);

    for (unsigned i = numAliveObjects; i < endIndex; ++i)
    {
      dataArray_.Data(i) = A();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorNode_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////