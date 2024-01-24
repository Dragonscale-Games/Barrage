/* ======================================================================== */
/*!
 * \file            SpawnRandomSpeed.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRandomSpeed.hpp"
#include "Objects/Pools/Pool.hpp"
#include "Spaces/Space.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RandomSpeed::RandomSpeed() : SpawnRuleT<RandomSpeedData>("RandomSpeed") {}

    std::shared_ptr<SpawnRule> RandomSpeed::Clone() const
    {
      return std::make_shared<RandomSpeed>(*this);
    }

    void RandomSpeed::Execute(SpawnRuleInfo& info)
    {
      Random& rng = info.space_.RNG();
      VelocityArray& dest_velocities = info.destinationPool_.GetComponentArray<Velocity>("Velocity");

      for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
      {
        float speed = rng.RangeFloat(data_.minSpeed_, data_.maxSpeed_);

        for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            Velocity& dest_velocity = dest_velocities.Data(dest_index);

            dest_velocity.SetSpeed(speed);
          }
        }
      }
    }

    void RandomSpeed::SetRTTRValue(const rttr::variant& value)
    {
      SpawnRuleT<RandomSpeedData>::SetRTTRValue(value);

      if (data_.minSpeed_ < MINIMUM_SPEED)
      {
        data_.minSpeed_ = MINIMUM_SPEED;
      }
      
      if (data_.maxSpeed_ < data_.minSpeed_)
      {
        data_.maxSpeed_ = data_.minSpeed_;
      }
    }

    void RandomSpeed::Reflect()
    {
      rttr::registration::class_<Spawn::RandomSpeedData>("RandomSpeedData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("minSpeed", &Spawn::RandomSpeedData::minSpeed_)
        .property("maxSpeed", &Spawn::RandomSpeedData::maxSpeed_)
        ;
    }
  }
}