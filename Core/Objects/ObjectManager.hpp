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

#include "Pools/PoolManager.hpp"
#include "Systems/SystemManager.hpp"
#include "Spawning/SpawnFunctionManager.hpp"
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
      // Systems
      // ===================================================================

      std::vector<std::string_view> GetRegisteredSystemNames();

      std::vector<std::string_view> GetSystemUpdateOrder();

      // ===================================================================
      // Pools
      // ===================================================================

      void CreatePool(const PoolArchetype& archetype);

      Pool* GetPool(const std::string& name) const;

      void DeletePool(const std::string& poolName);

      void DeleteAllPools();

      std::vector<std::string> GetPoolNames();
    
    private:
      template <typename T>
      void RegisterComponent(const std::string_view& componentName);
      
      template <typename T>
      void RegisterComponentArray(const std::string_view& componentName);

      template <typename T>
      void RegisterSystem(const std::string_view& systemName);

      void RegisterSpawnFunction(const std::string_view& name, SpawnFunction spawnFunction);

      void SetSystemUpdateOrder(const std::vector<std::string_view>& updateOrderList);

      void RegisterCustomComponents();

      void RegisterCustomSystems();

      void RegisterCustomSpawnFunctions();

      void SetSystemUpdateOrder();

    private:
      PoolManager poolManager_;
      SystemManager systemManager_;
	};
}

#include "ObjectManager.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////