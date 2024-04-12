/* ======================================================================== */
/*!
 * \file            Component.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component class that all components should inherit from.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Component_BARRAGE_T
#define Component_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  ComponentT<T>::ComponentT() :
    data_()
  {
  }

  template <typename T>
  std::shared_ptr<Component> ComponentT<T>::Clone() const
  {
    return std::make_shared<ComponentT<T>>(*this);
  }

  template <typename T>
  void ComponentT<T>::CopyToThis(const Component& source)
  {
    const ComponentT<T>& source_derived = static_cast<const ComponentT<T>&>(source);

    data_ = source_derived.data_;
  }

  template <typename T>
  void ComponentT<T>::SetCapacity([[maybe_unused]] unsigned capacity)
  {
    // intentionally empty, should be specialized in component classes that have per-object data
  }

  template <typename T>
  void ComponentT<T>::HandleDestructions(
    [[maybe_unused]] const Destructible* destructionArray,
    [[maybe_unused]] unsigned writeIndex,
    [[maybe_unused]] unsigned endIndex)
  {
    // intentionally empty, should be specialized in component classes that have per-object data
  }

  template <typename T>
  T& ComponentT<T>::Data()
  {
    return data_;
  }

  template <typename T>
  rttr::variant ComponentT<T>::GetRTTRValue() const
  {
    rttr::variant value = data_;

    return value;
  }

  template <typename T>
  void ComponentT<T>::SetRTTRValue(const rttr::variant& value)
  {
    if (value.get_type() != rttr::type::get<T>())
    {
      return;
    }

    data_ = value.get_value<T>();
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // Component_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////