/* ======================================================================== */
/*!
 * \file            SpawnType.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Holds all information needed to spawn a type of object in a pool.
*/
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnType_BARRAGE_H
#define SpawnType_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "SpawnLayer.hpp"

namespace Barrage
{
  class SpawnType
  {
    public:
      SpawnType();

      void CreateSpawn(unsigned sourceIndex);

      void ClearSpawns();

      void FinalizeGroupInfo();

      unsigned GetNumberOfObjectsToSpawn();

    private:
      std::vector<unsigned> sourceIndices_;
      std::vector<SpawnLayer> spawnLayers_;
      std::string destinationPoolName_;
      std::string spawnArchetypeName_;

      friend class Pool;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnType_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////