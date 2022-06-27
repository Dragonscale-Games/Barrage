/* ======================================================================== */
/*!
 * \file            PoolArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of shared
   components using its shared component map. Only provides names of component
   arrays, as components in component arrays are initialized later with an
   ObjectArchetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolArchetype_BARRAGE_H
#define PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/EngineComponents.hpp"

namespace Barrage
{
  //! Used to initialize an object pool
  class PoolArchetype
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes the archetype with an empty map of components.
      */
      /**************************************************************/
      PoolArchetype();

      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to pool archetype.
      */
      /**************************************************************/
      ~PoolArchetype();

    public:
      SharedComponentMap sharedComponents_;          //!< Map of initialized shared components to copy
      std::vector<std::string> componentArrayNames_; //!< List of names of component arrays to add to pool
      std::vector<std::string> tags_;                //!< Tags that the new pool will have
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////