/* ======================================================================== */
/*!
 * \file            PoolManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolManager_BARRAGE_H
#define PoolManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Pool.hpp"
#include "Objects/Components/ComponentAllocator.hpp"
#include "Objects/Archetypes/PoolArchetype/PoolArchetype.hpp"

namespace Barrage
{
  //! Maps system names to systems
  typedef std::unordered_map<std::string, Pool*> PoolMap;
  
  //! List of pool names
  typedef std::vector<std::string> PoolList;

  //! <class description>
  class PoolManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      PoolManager(ComponentAllocator& componentAllocator);

      /**************************************************************/
      /*!
        \brief
          Deallocates all pools that are still allocated.
      */
      /**************************************************************/
      ~PoolManager();

      /**************************************************************/
      /*!
        \brief
          Constructs an object pool and adds all component types
          contained in the input archetype.

        \param name
          The name of the object pool. If an object pool with that name
          already exists, the pool is not constructed.

        \param archetype
          The archetype carrying information about all the components
          the new object pool will contain.

        \param capacity
          The maximum number of objects the pool will be able to hold.

        \return
          Returns a pointer to the newly created object pool. Returns
          nullptr if creation fails.
      */
      /**************************************************************/
      Pool* CreatePool(const std::string& name, const PoolArchetype& archetype, unsigned capacity);

      /**************************************************************/
      /*!
        \brief
          Gets an object pool if it exists. If it doesn't exist,
          returns nullptr.

        \param name
          The name of the object pool.

        \return
          Returns the object pool if it exists, returns nullptr
          otherwise.
      */
      /**************************************************************/
      Pool* GetPool(const std::string& name) const;

      /**************************************************************/
      /*!
        \brief
          Deletes the object pool with the given name. If no object
          pool has that name, simply does nothing.

        \param name
          The name of the object pool. 
      */
      /**************************************************************/
      void DeletePool(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Deletes the object pool with the given name. If no object
          pool has that name, simply does nothing.

        \return
          Returns the names of all currently active pools.
      */
      /**************************************************************/
      PoolList GetPoolNames();

    private:
      /**************************************************************/
      /*!
        \brief
          Called by the public CreatePool to create an object pool.

        \param archetype
          The archetype carrying information about all the components
          the new object pool will contain.

        \param capacity
          The maximum number of objects the pool will be able to hold.

        \return
          Returns a pointer to the newly created object pool. Returns
          nullptr if creation fails.
      */
      /**************************************************************/
      Pool* CreatePoolInternal(const PoolArchetype& archetype, unsigned capacity);

    private:
      PoolMap pools_;                          //!< The collection of all object pools
      ComponentAllocator& componentAllocator_; //!< Component allocator the pool manager will use
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////