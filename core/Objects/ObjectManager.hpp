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
#include "Initializers/InitializerManager.hpp"

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

      ObjectComponentList GetObjectComponentNames();

      PoolComponentList GetPoolComponentNames();

      // ===================================================================
      // Initializers
      // ===================================================================

      InitializerList GetInitializerNames();

      // ===================================================================
      // Systems
      // ===================================================================

      SystemList GetRegisteredSystemNames();

      SystemList GetSystemUpdateOrder();

      // ===================================================================
      // Pools
      // ===================================================================

      void AddPoolArchetype(const std::string& name, PoolArchetype* archetype);

      void CreatePool(const std::string& poolName, const std::string& archetypeName, unsigned capacity = 1);

      Pool* GetPool(const std::string& name) const;

      void DeletePool(const std::string& poolName);

      void DeleteAllPools();

      ArchetypeList GetPoolArchetypeNames();

      PoolList GetPoolNames();

      // ===================================================================
      // Objects
      // ===================================================================

      void AddObjectArchetype(const std::string& name, ObjectArchetype* archetype);

      void CreateObject(const std::string& poolName, const std::string& archetypeName);

      ArchetypeList GetObjectArchetypeNames();
    
    private:
      template <typename T>
      void RegisterComponent(const std::string& componentName);

      template <typename T>
      void RegisterSystem(const std::string& systemName);

      void RegisterInitializer(const std::string name, Initializer initializer);

      void SetSystemUpdateOrder(const SystemList& updateOrderList);

      void RegisterCustomComponents();

      void RegisterCustomSystems();

      void RegisterCustomInitializers();

      void SetCustomSystemUpdateOrder();

    private:
      ComponentAllocator componentAllocator_;
      ArchetypeManager archetypeManager_;
      PoolManager poolManager_;
      SystemManager systemManager_;
      InitializerManager initializerManager_;
	};
}

#include "ObjectManager.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////