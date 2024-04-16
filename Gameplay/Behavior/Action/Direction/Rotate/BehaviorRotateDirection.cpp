/* ======================================================================== */
/*!
 * \file            BehaviorRotateDirection.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

#include "BehaviorRotateDirection.hpp"
#include "ComponentArrays/Velocity/VelocityArray.hpp"
#include <glm/glm.hpp>

namespace Barrage
{
  namespace Behavior
  {
    RotateDirection::RotateDirection() : BehaviorNodeT<RotateDirectionData>("RotateDirection", BehaviorNodeType::Action) {};

    std::shared_ptr<BehaviorNode> RotateDirection::Clone() const
    {
      return std::make_shared<RotateDirection>(*this);
    }

    BehaviorState RotateDirection::Execute(BehaviorNodeInfo& info)
    {
      Velocity& velocity = info.pool_.GetComponentArray<Velocity>("Velocity").Data(info.objectIndex_);

      velocity.Rotate(data_.cosineAngle_, data_.sinAngle_);

      return BehaviorState::Success();
    }

    void RotateDirection::SetRTTRValue(const rttr::variant& value)
    {
      BehaviorNodeT<RotateDirectionData>::SetRTTRValue(value);

      data_.cosineAngle_ = glm::cos(data_.angle_.value_);
      data_.sinAngle_ = glm::sin(data_.angle_.value_);
    }

    void RotateDirection::Reflect()
    {
      rttr::registration::class_<Behavior::RotateDirectionData>("RotateDirectionData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("angle", &Behavior::RotateDirectionData::angle_)
        ;
    }
  }
}