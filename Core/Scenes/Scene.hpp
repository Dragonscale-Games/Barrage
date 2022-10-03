/* ======================================================================== */
/*!
 * \file            Scene.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a list of pools and game objects to spawn in a space.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Scene_BARRAGE_H
#define Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Pools/PoolInfo.hpp>

namespace Barrage
{  
  //! contains all the information needed for a space to run a simulation
  class Scene
	{
    public:   
      Scene();

      void AddStartingPool(const PoolInfo& startingPool);

      std::vector<PoolInfo> startingPools_; //!< List of pools and objects the scene starts with
      unsigned long long rngSeed_;          //!< The starting rng seed of the scene
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////