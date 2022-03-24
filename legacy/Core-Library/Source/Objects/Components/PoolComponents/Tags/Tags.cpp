/* ======================================================================== */
/*!
 * \file            Tags.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

#include "stdafx.h"
#include "Tags.hpp"

namespace Barrage
{
  Tags::Tags() :
    tagSet_()
  {
  }

  bool Tags::HasTag(const std::string& tag) const
  {
    return tagSet_.count(tag);
  }
}