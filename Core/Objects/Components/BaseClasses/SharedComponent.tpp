/* ======================================================================== */
/*!
 * \file            SharedComponent.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base shared component class that all shared components should inherit from.
   A shared component is a component that all objects in a pool use.
   For instance, all objects in a pool may use the same sprite component.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SharedComponent_BARRAGE_T
#define SharedComponent_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  SharedComponentT<T>::SharedComponentT() :
    data_()
  {
  }

  template <typename T>
  void SharedComponentT<T>::CopyToThis(const SharedComponent& source)
  {
    const SharedComponentT<T>& source_derived = static_cast<const SharedComponentT<T>&>(source);

    data_ = source_derived.data_;
  }

  template <typename T>
  T& SharedComponentT<T>::Data()
  {
    return data_;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // SharedComponent_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////