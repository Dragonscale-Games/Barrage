/* ======================================================================== */
/*!
 * \file            LifetimeArray.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "LifetimeArray.hpp"

namespace Barrage
{
  Lifetime::Lifetime() :
    ticks_(120)
  {
  }

  void Lifetime::Reflect()
  {
    rttr::registration::class_<Lifetime>("Lifetime")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("ticks", &Lifetime::ticks_)
      ;
  }
}