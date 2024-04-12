/* ======================================================================== */
/*!
 * \file            BehaviorWait.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorWait.hpp"

namespace Barrage
{
  namespace Behavior
  {
    WaitData::WaitData() :
      numTicks_(120)
    {
    }
    
    WaitArrayElement::WaitArrayElement() :
      elapsedTicks_(0)
    {
    }

    Wait::Wait() : BehaviorNodeTA<WaitData, WaitArrayElement>("Wait", BehaviorNodeType::Action) {};

    std::shared_ptr<BehaviorNode> Wait::Clone() const
    {
      return std::make_shared<Wait>(*this);
    }

    BehaviorState Wait::Execute(BehaviorNodeInfo& info)
    {
      unsigned& elapsedTicks = dataArray_.Data(info.objectIndex_).elapsedTicks_;

      elapsedTicks++;

      if (elapsedTicks <= data_.numTicks_)
      {
        return BehaviorState::Running();
      }
      else
      {
        return BehaviorState::Success();
      }
    }

    void Wait::Reflect()
    {
      rttr::registration::class_<Behavior::WaitData>("WaitData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("numTicks", &Behavior::WaitData::numTicks_)
        ;
    }
  }
}