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
      ticks_(0)
    {
    }
    
    Wait::Wait() : BehaviorNodeT<WaitData>("Wait", BehaviorNodeType::Decorator) {};

    std::shared_ptr<BehaviorNode> Wait::Clone() const
    {
      return std::make_shared<Wait>(*this);
    }

    void Wait::Reflect()
    {
      rttr::registration::class_<Behavior::WaitData>("WaitData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("ticks", &Behavior::WaitData::ticks_)
        ;
    }
  }
}