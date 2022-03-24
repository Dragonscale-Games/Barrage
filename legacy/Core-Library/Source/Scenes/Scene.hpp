/* ======================================================================== */
/*!
 * \file            Scene.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a set of instructions
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Scene_BARRAGE_H
#define Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

namespace Barrage
{
  typedef std::vector<std::string> ObjectList;
  
  //! contains all the information needed for a space to run a simulation
  class Scene
	{
    public:
      //! contains all information needed to create a pool and populate it with objects
      class PoolInfo
      {
        public:
          PoolInfo(const std::string& poolName, const std::string& archetypeName, unsigned capacity = 1);

          void AddObject(const std::string& archetypeName);

          const std::string& GetPoolName() const;

          const std::string& GetPoolArchetypeName() const;

          unsigned GetPoolCapacity() const;

          const ObjectList& GetObjectList() const;

        private:
          std::string poolName_;      //!< Name that will be assigned to the pool
          std::string archetypeName_; //!< Name of the archetype used to construct the pool
          unsigned capacity_;         //!< Number of objects the pool can hold
          ObjectList objects_;        //!< Names of object archetypes used to construct starting objects
      };
  
    public:   
      Scene();

      void AddStartingPool(const PoolInfo& startingPool);

      const std::vector<PoolInfo>& GetStartingPools() const;

    private:
      std::vector<PoolInfo> startingPools_; //!< List of pools and objects the scene starts with
      unsigned long long startingSeed_;     //!< The starting seed for the scene's random number generator
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////