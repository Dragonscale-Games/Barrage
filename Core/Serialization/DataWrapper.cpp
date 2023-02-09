/* ======================================================================== */
/*!
 * \file            DataWrapper.cpp
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

#include "DataWrapper.hpp"

namespace Barrage
{
  DataWrapper::DataWrapper(void* dataPointer) :
    dataPointer_(dataPointer),
    representation_(Representation::RAW)
  {
  }

  DataWrapper::DataWrapper(rttr::variant& dataVariant) :
    dataPointer_(&dataVariant),
    representation_(Representation::RTTR_VARIANT)
  {
  }
}