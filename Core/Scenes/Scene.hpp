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
#include <unordered_map>

namespace Barrage
{  
  typedef std::unordered_map<std::string, PoolInfo> PoolInfoMap;
  
  //! contains all the information needed for a space to run a simulation
  class Scene
	{
    public:   
      Scene();

      bool HasPool(const std::string& poolName);

      void AddStartingPool(const PoolInfo& startingPool);

      bool HasObject(const std::string& poolName, const std::string& objectName);

      void AddObject(const std::string& poolName, const std::string& objectName);

      PoolInfoMap startingPools_; //!< Collection of pools and objects the scene starts with
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////