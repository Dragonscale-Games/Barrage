#pragma once
/* ======================================================================== */
/*!
 * \file            SpawnScaleOrigin.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnScaleOrigin.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    ScaleOrigin::ScaleOrigin() : SpawnRule("ScaleOrigin") {}

    std::shared_ptr<SpawnRule> ScaleOrigin::Clone() const
    {
      return std::make_shared<ScaleOrigin>(*this);
    }

    void ScaleOrigin::Execute(SpawnRuleInfo& info)
    {

      for (unsigned layerCopy = 0; layerCopy < info.groupInfo_.numLayerCopies_; ++layerCopy)
      {
        for (unsigned group = 0; group < info.groupInfo_.numGroups_; ++group)
        {
          for (unsigned object = 0; object < info.groupInfo_.numObjectsPerGroup_; ++object)
          {
            unsigned dest_index = CalculateDestinationIndex(info, object, group, layerCopy);

          }
        }
      }
    }
  }
}