/* ======================================================================== */
/*!
 * \file            Registrar.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of system via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Registrar.hpp"

namespace Barrage
{
  std::vector<std::string> Registrar::systemUpdateOrder_ = std::vector<std::string>();
  
  std::vector<std::string>& Registrar::GetSystemUpdateOrder()
  {
    return systemUpdateOrder_;
  }

  void Registrar::RegisterTag(const std::string& tag)
  {
    
  }

  void Registrar::SetSystemUpdateOrder(const std::vector<std::string>& updateOrder)
  {
    systemUpdateOrder_ = updateOrder;
  }
}
