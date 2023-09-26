/* ======================================================================== */
/*!
 * \file            Pool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   An object pool is a block of memory that can hold a prespecified number
   of objects with a specific combination of components.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Pool_BARRAGE_H
#define Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Archetypes/PoolArchetype.hpp"
#include "Objects/Components/Component.hpp"
#include "Objects/Components/ComponentArray.hpp"

namespace Barrage
{
  //! Container for a prespecified number of objects
  class Pool
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs an object pool.

        \param archetype
          The archetype to construct the pool from.
      */
      /**************************************************************/
      Pool(const PoolArchetype& archetype);

    private:
      ComponentMap components_;            //!< Holds shared components and their names
      ComponentArrayMap componentArrays_;  //!< Holds component arrays and their names
      ObjectArchetypeMap spawnArchetypes_; //!< Objects that can be spawned in this pool
      StringSet tags_;                     //!< Holds the pool's tags
      unsigned numActiveObjects_;          //!< Number of currently active objects
      unsigned numQueuedObjects_;          //!< Number of objects ready to be spawned on the next tick
      unsigned capacity_;                  //!< Total number of objects the pool can hold
      std::string name_;                   //!< Name of the pool
  };
}

#include "Pool.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////