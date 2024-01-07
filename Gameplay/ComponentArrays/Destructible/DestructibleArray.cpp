/* ======================================================================== */
/*!
 * \file            DestructibleArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "DestructibleArray.hpp"

namespace Barrage
{
  void DestructibleReflect()
  {
    rttr::registration::class_<Destructible>("Destructible")
      .constructor<>() (rttr::policy::ctor::as_object)
      ;
  }
}