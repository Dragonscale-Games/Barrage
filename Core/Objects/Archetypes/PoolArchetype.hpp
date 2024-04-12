/* ======================================================================== */
/*!
 * \file            PoolArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of components
   on the pool. Only provides names of component arrays, as components in
   component arrays are initialized later with an ObjectArchetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolArchetype_BARRAGE_H
#define PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/Component.hpp"
#include "Objects/Archetypes/ObjectArchetype.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  //! Used to initialize an object pool
  class PoolArchetype
  {
    public:
      PoolArchetype();
      
      /**************************************************************/
      /*!
        \brief
          Constructs the pool archetype.

        \param name
          The name of the pool this archetype will create.
      */
      /**************************************************************/
      PoolArchetype(const std::string& name, unsigned capacity = 1);

      const std::string& GetName() const;

    public:
      std::string name_;              //!< Name of the pool this archetype will create
      unsigned capacity_;             //!< The number of objects the pool will be able to hold
      ComponentMap components_;       //!< Initialized components to copy to the pool
      StringSet componentArrayNames_; //!< Names of the pool's component arrays
      StringSet tags_;                //!< Tags of the pool

      ObjectArchetypeMap startingObjects_; //!< Objects present in the pool at the start of a scene
      ObjectArchetypeMap spawnArchetypes_; //!< Objects that can be spawned in the pool

      friend class Pool;
  };

  using PoolArchetypeMap = std::map<std::string, PoolArchetype>;
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////