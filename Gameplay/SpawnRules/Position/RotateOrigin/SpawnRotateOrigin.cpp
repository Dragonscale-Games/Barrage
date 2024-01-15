#pragma once
/* ======================================================================== */
/*!
 * \file            SpawnRotateOrigin.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief


   Requirements:

 */
 /* ======================================================================== */

#include <stdafx.h>
#include "SpawnRotateOrigin.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Spawn
  {
    RotateOrigin::RotateOrigin() : SpawnRule("RotateOrigin") {}

    std::shared_ptr<SpawnRule> RotateOrigin::Clone() const
    {
      return std::make_shared<RotateOrigin>(*this);
    }

    void RotateOrigin::Execute(SpawnRuleInfo& info)
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