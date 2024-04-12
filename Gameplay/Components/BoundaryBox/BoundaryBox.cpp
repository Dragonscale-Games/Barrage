/* ======================================================================== */
/*!
 * \file            BoundaryBox.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BoundaryBox.hpp"

namespace Barrage
{
  BoundaryBox::BoundaryBox() : 
    xMin_(-50.0f), 
    xMax_(50.0f), 
    yMin_(-50.0f), 
    yMax_(50.0f) 
  {
  }

  void BoundaryBox::Reflect()
  {
    rttr::registration::class_<BoundaryBox>("BoundaryBox")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("xMin", &BoundaryBox::xMin_)
      .property("xMax", &BoundaryBox::xMax_)
      .property("yMin", &BoundaryBox::yMin_)
      .property("yMax", &BoundaryBox::yMax_)
      ;
  }
}