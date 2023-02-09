/* ======================================================================== */
/*!
 * \file            DataWrapper.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Generic data wrapper. This class is used to wrap a pointer or RTTR variant
   in a convenient interface for getting/setting the value of the underlying
   object. The wrapper should not outlive the object it represents.

   Very unsafe! These are basically fancy void pointers. Use at your own risk.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef DataWrapper_BARRAGE_H
#define DataWrapper_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <rttr/variant.h>

namespace Barrage
{
  //! Convenient interface for working with void pointers
  class DataWrapper
  {
    enum class Representation
    {
      RAW,
      RTTR_VARIANT
    };
  
    public:
      DataWrapper(void* dataPointer);

      DataWrapper(rttr::variant& dataVariant);

      template <typename T>
      T GetValue();

      template <typename T>
      void SetValue(const T& newValue);

    private:
      void* dataPointer_;
      Representation representation_;
  };
}

#include "DataWrapper.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // DataWrapper_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////