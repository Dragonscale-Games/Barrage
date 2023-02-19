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

      ComponentAllocator& GetComponentAllocator();

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

      void CreatePoolArchetype(const std::string& name);

      void AddPoolArchetype(const std::string& name, PoolArchetype* archetype);

      PoolArchetype* GetPoolArchetype(const std::string& name);

      PoolArchetype* ExtractPoolArchetype(const std::string& name);

      void DeletePoolArchetype(const std::string& name);

      void CreatePool(const std::string& poolName);

      void CreatePoolAndObjects(const PoolInfo& poolInfo);

      Pool* GetPool(const std::string& name) const;

      void DeletePool(const std::string& poolName);

      void DeleteAllPools();

      std::vector<std::string> GetPoolArchetypeNames();

      std::vector<std::string> GetPoolNames();

      // ===================================================================
      // Objects
      // ===================================================================

      void CreateObjectArchetype(const std::string& name, const std::vector<std::string_view>& componentArrayNames);

      void AddObjectArchetype(const std::string& name, ObjectArchetype* archetype);

      ObjectArchetype* GetObjectArchetype(const std::string& name);

      ObjectArchetype* ExtractObjectArchetype(const std::string& name);

      void DeleteObjectArchetype(const std::string& name);

      void CreateObject(const std::string& poolName, const std::string& archetypeName);

      std::vector<std::string> GetObjectArchetypeNames();
    
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