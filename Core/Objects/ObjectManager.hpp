/* ======================================================================== */
/*!
 * \file            ObjectManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main point of contact for game object manipulation.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectManager_BARRAGE_H
#define ObjectManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Archetypes/ArchetypeManager.hpp"
#include "Pools/PoolManager.hpp"
#include "Pools/PoolInfo.hpp"
#include "Systems/SystemManager.hpp"
#include "SpawnFuncs/SpawnFuncManager.hpp"
#include "Random/Random.hpp"

namespace Barrage
{ 
  class Space;
  
  //! Main point of contact for game object manipulation
  class ObjectManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor. Registers default engine components,
          systems, and initializers.
      */
      /**************************************************************/
      ObjectManager(Space& space);

      // ===================================================================
      // Game loop
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Updates all objects.
      */
      /**************************************************************/
      void Update();
      
      /**************************************************************/
      /*!
        \brief
          Draws all objects.
      */
      /**************************************************************/
      void Draw();

      // ===================================================================
      // Components
      // ===================================================================

      std::vector<std::string_view> GetComponentArrayNames();

      std::vector<std::string_view> GetSharedComponentNames();

      // ===================================================================
      // Initializers
      // ===================================================================

      std::vector<std::string_view> GetSpawnFuncNames();

      // ===================================================================
      // Systems
      // ===================================================================

      std::vector<std::string_view> GetRegisteredSystemNames();

      std::vector<std::string_view> GetSystemUpdateOrder();

      // ===================================================================
      // Pools
      // ===================================================================

      void AddPoolArchetype(const std::string_view& name, PoolArchetype* archetype);

      PoolArchetype* GetPoolArchetype(const std::string_view& name);

      void CreatePool(const std::string_view& poolName, const std::string_view& archetypeName, unsigned capacity = 1);

      void CreatePoolAndObjects(const PoolInfo& poolInfo);

      Pool* GetPool(const std::string_view& name) const;

      void DeletePool(const std::string_view& poolName);

      void DeleteAllPools();

      std::vector<std::string_view> GetPoolArchetypeNames();

      std::vector<std::string_view> GetPoolNames();

      // ===================================================================
      // Objects
      // ===================================================================

      void AddObjectArchetype(const std::string_view& name, ObjectArchetype* archetype);

      ObjectArchetype* GetObjectArchetype(const std::string_view& name);

      void CreateObject(const std::string_view& poolName, const std::string_view& archetypeName);

      std::vector<std::string_view> GetObjectArchetypeNames();
    
    private:
      template <typename T>
      void RegisterComponent(const std::string_view& componentName);

      template <typename T>
      void RegisterSystem(const std::string_view& systemName);

      void RegisterSpawnFunc(const std::string_view& name, SpawnFunc spawnFunction);

      void SetSystemUpdateOrder(const std::vector<std::string_view>& updateOrderList);

      void RegisterEngineComponents();

      void RegisterEngineSystems();

      void RegisterEngineSpawnFuncs();

      void SetDefaultSystemUpdateOrder();

      void RegisterCustomComponents();

      void RegisterCustomSystems();

      void RegisterCustomSpawnFuncs();

      void SetSystemUpdateOrder();

    private:
      Random rng_;
      ComponentAllocator componentAllocator_;
      ArchetypeManager archetypeManager_;
      PoolManager poolManager_;
      SystemManager systemManager_;
      SpawnFuncManager spawnFuncManager_;
	};
}

#include "ObjectManager.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////