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
  ComponentArrayT<T>::ComponentArrayT() :
    data_(nullptr)
  {
  }
  
  template <typename T>
  ComponentArrayT<T>::~ComponentArrayT()
  {
    delete[] data_;
  }

  template <typename T>
  void ComponentArrayT<T>::Allocate(unsigned capacity)
  {
    if (data_)
    {
      delete[] data_;
    }
      
    data_ = new T[capacity];
  }

  template <typename T>
  void ComponentArrayT<T>::CopyToThis(const ComponentArray& source, unsigned sourceIndex, unsigned recipientIndex)
  {
    const ComponentArrayT<T>& source_derived = static_cast<const ComponentArrayT<T>&>(source);

    data_[recipientIndex] = source_derived.data_[sourceIndex];
  }
  
  template <typename T>
  T& ComponentArrayT<T>::operator[](int i)
  {
    return data_[i];
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentArray_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////