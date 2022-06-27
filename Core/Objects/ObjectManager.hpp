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
#include "Systems/SystemManager.hpp"
#include "SpawnFuncs/SpawnFuncManager.hpp"

namespace Barrage
{ 
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
      ObjectManager();

      // ===================================================================
      // Game loop
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Initializes the game object manager.
      */
      /**************************************************************/
      void Initialize();

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

      std::vector<std::string> GetComponentArrayNames();

      std::vector<std::string> GetSharedComponentNames();

      // ===================================================================
      // Initializers
      // ===================================================================

      std::vector<std::string> GetSpawnFuncNames();

      // ===================================================================
      // Systems
      // ===================================================================

      std::vector<std::string> GetRegisteredSystemNames();

      std::vector<std::string> GetSystemUpdateOrder();

      // ===================================================================
      // Pools
      // ===================================================================

      void AddPoolArchetype(const std::string& name, PoolArchetype* archetype);

      void CreatePool(const std::string& poolName, const std::string& archetypeName, unsigned capacity = 1);

      Pool* GetPool(const std::string& name) const;

      void DeletePool(const std::string& poolName);

      void DeleteAllPools();

      std::vector<std::string> GetPoolArchetypeNames();

      PoolList GetPoolNames();

      // ===================================================================
      // Objects
      // ===================================================================

      void AddObjectArchetype(const std::string& name, ObjectArchetype* archetype);

      void CreateObject(const std::string& poolName, const std::string& archetypeName);

      std::vector<std::string> GetObjectArchetypeNames();
    
    private:
      template <typename T>
      void RegisterComponent(const std::string& componentName);

      template <typename T>
      void RegisterSystem(const std::string& systemName);

      void RegisterSpawnFunc(const std::string name, SpawnFunc spawnFunction);

      void SetSystemUpdateOrder(const std::vector<std::string>& updateOrderList);

      void RegisterEngineComponents();

      void RegisterEngineSystems();

      void RegisterEngineSpawnFuncs();

      void SetDefaultSystemUpdateOrder();

      void RegisterCustomComponents();

      void RegisterCustomSystems();

      void RegisterCustomSpawnFuncs();

      void SetSystemUpdateOrder();

      void CreateArchetypes();

    private:
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