/* ======================================================================== */
/*!
 * \file            SpawnType.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Holds all information needed to spawn a type of object in a pool.
*/
/* ======================================================================== */

#include "stdafx.h"
#include "SpawnType.hpp"

namespace Barrage
{
  SpawnType::SpawnType() :
    sourceIndices_(),
    spawnLayers_(),
    destinationPoolName_(),
    spawnArchetypeName_()
  {
  }

  void SpawnType::CreateSpawn(unsigned sourceIndex)
  {
    sourceIndices_.push_back(sourceIndex);
  }

  void SpawnType::ClearSpawns()
  {
    sourceIndices_.clear();
  }

  void SpawnType::FinalizeGroupInfo()
  {
    size_t numLayers = spawnLayers_.size();
    
    // start at second layer
    for (size_t i = 1; i < numLayers; ++i)
    {
      SpawnLayer& previousLayer = spawnLayers_[i - 1];
      SpawnLayer& currentLayer = spawnLayers_[i];

      for (auto it = sourceIndices_.begin(); it != sourceIndices_.end(); ++it)
      {
        unsigned sourceIndex = *it;
        GroupInfo& previousGroupInfo = previousLayer.groupInfoArray_.Data(sourceIndex);
        GroupInfo& currentGroupInfo = currentLayer.groupInfoArray_.Data(sourceIndex);

        previousGroupInfo.numLayerCopies_ = currentGroupInfo.numGroups_;
        currentGroupInfo.numObjectsPerGroup_ = previousGroupInfo.numGroups_ * previousGroupInfo.numObjectsPerGroup_;
      }
    }
  }

  unsigned SpawnType::GetNumberOfObjectsToSpawn()
  {
    unsigned numObjects = 0;
    
    if (!spawnLayers_.empty())
    {
      SpawnLayer& lastLayer = spawnLayers_.back();

      for (auto it = sourceIndices_.begin(); it != sourceIndices_.end(); ++it)
      {
        unsigned sourceIndex = *it;
        GroupInfo& groupInfo = lastLayer.groupInfoArray_.Data(sourceIndex);
        
        numObjects += groupInfo.numGroups_ * groupInfo.numObjectsPerGroup_;
      }
    }

    return numObjects;
  }
}