#pragma once
/* ======================================================================== */
/*!
 * \file            SpawnSpacedFan.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnSpacedFan.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    SpacedFan::SpacedFan() : SpawnRule("SpacedFan") {}

    std::shared_ptr<SpawnRule> SpacedFan::Clone() const
    {
      return std::make_shared<SpacedFan>(*this);
    }

    void SpacedFan::Execute(SpawnRuleInfo& info)
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