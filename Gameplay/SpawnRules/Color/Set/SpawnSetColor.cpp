
/* ======================================================================== */
/*!
 * \file            SpawnIncrementCount.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnSetColor.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    SetColor::SetColor() : SpawnRuleT<SetColorData>("SetColor") {}

    std::shared_ptr<SpawnRule> SetColor::Clone() const
    {
      return std::make_shared<SetColor>(*this);
    }

    void SetColor::Execute(SpawnRuleInfo& info)
    {
      ColorTintArray& dest_colors = info.destinationPool_.GetComponentArray<ColorTint>("ColorTint");

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);
            ColorTint& dest_color = dest_colors.Data(dest_index);
            dest_color = data_.color_;
          }
        }
      }
    }

    SpawnRuleStage SetColor::GetStage()
    {
      return SpawnRuleStage::VALUE_RULE;
    }

    void SetColor::Reflect()
    {
      rttr::registration::class_<Spawn::SetColorData>("SetColorData")
        .constructor<>() (rttr::policy::ctor::as_object)
        .property("color", &Spawn::SetColorData::color_)
        ;
    }
  }
}