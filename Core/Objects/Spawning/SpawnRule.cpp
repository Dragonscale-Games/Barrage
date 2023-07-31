/* ======================================================================== */
/*!
 * \file            SpawnRule.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A spawn rule modifies the initial values of a newly spawned object.
 */
 /* ======================================================================== */

#include "SpawnRule.hpp"
#include "stdafx.h"

namespace Barrage
{
  SpawnRule::SpawnRule(const std::string& name) : name_(name)
  {
  }
  
  const std::string& SpawnRule::GetName() const
  {
    return name_;
  }
  
  rttr::variant SpawnRule::GetRTTRValue()
  {
    return rttr::variant();
  }

  void SpawnRule::SetRTTRValue(const rttr::variant& value)
  {
    UNREFERENCED(value);
  }
}