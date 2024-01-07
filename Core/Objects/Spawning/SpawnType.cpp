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
    destinationPool_(),
    spawnArchetype_()
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

    if (numLayers == 0)
    {
      return;
    }

    SpawnLayer& lastLayer = spawnLayers_.back();
    
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

        unsigned numObjectsInPreviousLayer = previousGroupInfo.numGroups_ * previousGroupInfo.numObjectsPerGroup_;

        currentGroupInfo.numObjectsPerGroup_ = numObjectsInPreviousLayer;
      }
    }

    // start at second layer
    for (size_t i = 1; i < numLayers; ++i)
    {
      SpawnLayer& previousLayer = spawnLayers_[i - 1];

      for (auto it = sourceIndices_.begin(); it != sourceIndices_.end(); ++it)
      {
        unsigned sourceIndex = *it;
        GroupInfo& previousGroupInfo = previousLayer.groupInfoArray_.Data(sourceIndex);
        GroupInfo& lastGroupInfo = lastLayer.groupInfoArray_.Data(sourceIndex);

        unsigned numObjectsInPreviousLayer = previousGroupInfo.numGroups_ * previousGroupInfo.numObjectsPerGroup_;
        unsigned totalObjectsInSpawn = lastGroupInfo.numGroups_ * lastGroupInfo.numObjectsPerGroup_;

        previousGroupInfo.numLayerCopies_ = totalObjectsInSpawn / numObjectsInPreviousLayer;
      }
    }
  }

  unsigned SpawnType::CalculateSpawnSize(unsigned maxSpawns)
  {
    unsigned totalSpawns = 0;
    
    if (!spawnLayers_.empty())
    {
      SpawnLayer& lastLayer = spawnLayers_.back();

      for (auto it = sourceIndices_.begin(); it != sourceIndices_.end(); ++it)
      {
        unsigned sourceIndex = *it;
        GroupInfo& groupInfo = lastLayer.groupInfoArray_.Data(sourceIndex);
        unsigned numSpawnsFromSource = groupInfo.numGroups_ * groupInfo.numObjectsPerGroup_;

        if (totalSpawns + numSpawnsFromSource <= maxSpawns)
        {
          totalSpawns += numSpawnsFromSource;
        }
        else
        {
          sourceIndices_.erase(it, sourceIndices_.end());
          break;
        }
      }
    }

    return totalSpawns;
  }

  void SpawnType::SetCapacity(unsigned capacity)
  {
    for (auto it = spawnLayers_.begin(); it != spawnLayers_.end(); ++it)
    {
      SpawnLayer& spawnLayer = *it;

      spawnLayer.SetCapacity(capacity);
    }
  }

  void SpawnType::HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex)
  {
    for (auto it = spawnLayers_.begin(); it != spawnLayers_.end(); ++it)
    {
      SpawnLayer& spawnLayer = *it;

      spawnLayer.HandleDestructions(destructionArray, writeIndex, endIndex);
    }
  }
}