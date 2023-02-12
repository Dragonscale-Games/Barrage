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
  //! contains all the information needed for a space to run a simulation
  class Scene
	{
    public:   
      Scene();

      bool HasPool(const std::string& poolName);

      void AddStartingPool(const PoolInfo& startingPool, unsigned* index = nullptr);

      PoolInfo* GetPoolInfo(const std::string& poolName);

      void RemovePool(const std::string& poolName, unsigned* index = nullptr);

      bool HasObject(const std::string& poolName, const std::string& objectName);

      void AddObject(const std::string& poolName, const std::string& objectName, unsigned* index = nullptr);

      void RemoveObject(const std::string& poolName, const std::string& objectName, unsigned* index = nullptr);

      std::vector<PoolInfo> startingPools_; //!< Collection of pools and objects the scene starts with
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////