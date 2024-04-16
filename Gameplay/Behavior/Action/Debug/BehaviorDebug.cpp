/* ======================================================================== */
/*!
 * \file            BehaviorDebug.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorDebug.hpp"

#include <iostream>

namespace Barrage
{
  namespace Behavior
  {
    Debug::Debug() : BehaviorNodeT<DebugData>("Debug", BehaviorNodeType::Action) {};
    
    std::shared_ptr<BehaviorNode> Debug::Clone() const
    {
      return std::make_shared<Debug>(*this);
    }

    BehaviorState Debug::Execute(BehaviorNodeInfo& info)
    {
      std::cout << data_.text_ << std::endl;

      return data_.succeeds_ ? BehaviorState::Success() : BehaviorState::Failure();
    }

    void Debug::Reflect()
    {
      rttr::registration::class_<Behavior::DebugData>("DebugData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("text", &Behavior::DebugData::text_)
        .property("succeeds", &Behavior::DebugData::succeeds_)
        ;
    }
  }
}