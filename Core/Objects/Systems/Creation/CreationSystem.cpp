/* ======================================================================== */
/*!
 * \file            CreationSystem.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles object creation both directly (through an object creation function)
   and indirectly (through updating object spawners).
 */
/* ======================================================================== */

#include "stdafx.h"
#include "CreationSystem.hpp"

namespace Barrage
{
  CreationSystem::CreationSystem() :
    System()
  {
    // this pool type has no required tags or components because all pools will be subscribed to the creation system
    PoolType all_pool_type;
    poolTypes_["All Pools"] = all_pool_type;

    /*PoolType handle_pool_type;
    handle_pool_type.AddSharedComponent("ObjectDirectory");
    handle_pool_type.AddComponentArray("DirectoryIndex");
    poolTypes_["Handle Pools"] = handle_pool_type;*/
  }

  void CreationSystem::Update()
  {
    //UpdatePoolGroup("Handle Pools", AssignHandles);
    UpdatePoolGroup("All Pools", SpawnObjects);
  }

  void CreationSystem::SpawnObjects(Pool* pool)
  {
    pool->numActiveObjects_ += pool->numQueuedObjects_;
    pool->numQueuedObjects_ = 0;
  }

  void CreationSystem::AssignHandles(Pool* pool)
  {
    ObjectDirectory& object_directory = pool->GetSharedComponent<ObjectDirectory>("ObjectDirectory")->Data();
    DirectoryIndexArray& directory_index_array = *pool->GetComponentArray<DirectoryIndex>("DirectoryIndex");

    unsigned start_index = pool->numActiveObjects_;
    unsigned num_queued_objects = pool->numQueuedObjects_;

    for (unsigned i = 0; i < num_queued_objects; ++i)
    {
      unsigned object_index = start_index + i;
      
      DirectoryIndex& directory_index = directory_index_array.Data(object_index);

      directory_index.index_ = object_directory.CreateHandle(object_index);
    }
  }
}