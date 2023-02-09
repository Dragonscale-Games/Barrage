/* ======================================================================== */
/*!
 * \file            DataWrapper.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Generic data wrapper. This class is used to wrap a pointer in a
   convenient interface for getting/setting the value of the underlying
   object. The wrapper should not outlive the object it points to.

   Very unsafe! These are basically just fancy void pointers. Use at your
   own risk.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef DataWrapper_BARRAGE_T
#define DataWrapper_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  T DataWrapper::GetValue()
  {
    if (representation_ == Representation::RTTR_VARIANT)
    {
      rttr::variant& variant = *static_cast<rttr::variant*>(dataPointer_);

      if (variant.get_type().is_pointer())
      {
        return *(variant.get_value<T*>());
      }
      else 
      {
        return variant.get_value<T>();
      }
    }
    else // representation_ == Representation::RAW
    {
      return *static_cast<T*>(dataPointer_);
    }
  }

  template <typename T>
  void DataWrapper::SetValue(const T& newValue)
  {
    if (representation_ == Representation::RTTR_VARIANT)
    {
      rttr::variant& variant = *static_cast<rttr::variant*>(dataPointer_);

      if (variant.get_type().is_pointer())
      {
        T& data = *(variant.get_value<T*>());
        data = newValue;
      }
      else
      {
        variant = newValue;
      }
    }
    else // representation_ == Representation::RAW
    {
      T& data = *static_cast<T*>(dataPointer_);
      data = newValue;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DataWrapper_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////