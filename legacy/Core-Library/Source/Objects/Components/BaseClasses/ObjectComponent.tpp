/* ======================================================================== */
/*!
 * \file            ObjectComponent.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base object component classes. NOTE: All object components should inherit
   from ObjectComponentTemplated, NOT ObjectComponent.

   An object component is a component that is unique per object that contains
   it.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectComponent_BARRAGE_T
#define ObjectComponent_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  ObjectComponentDerived<T>::ObjectComponentDerived() :
    data_(nullptr)
  {
  }
  
  template <typename T>
  ObjectComponentDerived<T>::~ObjectComponentDerived()
  {
    delete[] data_;
  }

  template <typename T>
  void ObjectComponentDerived<T>::Allocate(unsigned capacity)
  {
    data_ = new T[capacity];
  }

  template <typename T>
  void ObjectComponentDerived<T>::CopyToThis(const ObjectComponent& source, unsigned sourceIndex, unsigned recipientIndex)
  {
    const ObjectComponentDerived<T>& source_derived = static_cast<const ObjectComponentDerived<T>&>(source);

    data_[recipientIndex] = source_derived.data_[sourceIndex];
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectComponent_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////