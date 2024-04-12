/* ======================================================================== */
/*!
 * \file            BehaviorNodeFactory.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of behavior node via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "BehaviorNodeFactory.hpp"

namespace Barrage
{
  BehaviorNodeFactoryMethodMap BehaviorNodeFactory::behaviorNodeFactoryMethodMap_ = BehaviorNodeFactoryMethodMap();
  StringSet BehaviorNodeFactory::behaviorNodeNames_ = StringSet();

  DeepPtr<BehaviorNode> BehaviorNodeFactory::CreateBehaviorNode(const std::string& name)
  {
    if (behaviorNodeFactoryMethodMap_.count(name))
    {
      BehaviorNodeFactoryMethod function = behaviorNodeFactoryMethodMap_.at(name);
      return function();
    }
    else
    {
      return nullptr;
    }
  }

  const StringSet& BehaviorNodeFactory::GetBehaviorNodeNames()
  {
    return behaviorNodeNames_;
  }
}
