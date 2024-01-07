/* ======================================================================== */
/*!
 * \file            ComponentArray.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component array class that all component arrays should inherit from.
   Component arrays are used when each object in a pool needs its own copy
   of a component.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentArray_BARRAGE_T
#define ComponentArray_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  ComponentArrayT<T>::ComponentArrayT(unsigned capacity) :
    data_(nullptr),
    capacity_(capacity)
  {
    data_ = new T[capacity];
  }

  template <typename T>
  ComponentArrayT<T>::ComponentArrayT(const ComponentArrayT<T>& other) :
    data_(nullptr),
    capacity_(other.capacity_)
  {
    data_ = new T[capacity_];

    for (unsigned i = 0; i < capacity_; ++i)
    {
      data_[i] = other.data_[i];
    }
  }

  template <typename T>
  ComponentArrayT<T>& ComponentArrayT<T>::operator=(const ComponentArrayT<T>& other)
  {
    SetCapacity(other.capacity_);

    for (unsigned i = 0; i < capacity_; ++i)
    {
      data_[i] = other.data_[i];
    }

    return *this;
  }

  template <typename T>
  ComponentArrayT<T>::~ComponentArrayT()
  {
    delete[] data_;
  }

  template <typename T>
  void ComponentArrayT<T>::SetCapacity(unsigned capacity)
  {
    capacity_ = capacity;
    delete[] data_;
    data_ = new T[capacity_];
  }

  template <typename T>
  std::shared_ptr<ComponentArray> ComponentArrayT<T>::Clone() const
  {
    return std::make_shared<ComponentArrayT<T>>(*this);
  }

  template <typename T>
  void ComponentArrayT<T>::CopyToThis(const ComponentArray& source, unsigned sourceIndex, unsigned recipientIndex)
  {
    const ComponentArrayT<T>& source_derived = static_cast<const ComponentArrayT<T>&>(source);

    data_[recipientIndex] = source_derived.data_[sourceIndex];
  }

  template <typename T>
  unsigned ComponentArrayT<T>::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    for (unsigned i = writeIndex + 1; i < endIndex; ++i)
    {
      if (destructionArray[i].destroyed_ == false)
      {
        data_[writeIndex] = data_[i];
        ++writeIndex;
      }
    }

    // now that the array's packed, the number of alive objects is the same as the next write index
    return writeIndex;
  }

  template <typename T>
  T& ComponentArrayT<T>::Data(int index)
  {
    return data_[index];
  }

  template <typename T>
  rttr::variant ComponentArrayT<T>::GetRTTRValue(int index) const
  {
    rttr::variant value = data_[index];

    return value;
  }

  template <typename T>
  void ComponentArrayT<T>::SetRTTRValue(const rttr::variant& value, int index)
  {
    if (value.get_type() != rttr::type::get<T>())
    {
      return;
    }

    data_[index] = value.get_value<T>();
  }

  template <typename T>
  T* ComponentArrayT<T>::GetRaw()
  {
    return data_;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentArray_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////