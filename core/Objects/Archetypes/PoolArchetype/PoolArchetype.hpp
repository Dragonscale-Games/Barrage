/* ======================================================================== */
/*!
 * \file            PoolArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize an object pool. Provides starting values of pool
   components using its pool component map. Only provides names of object 
   components, as object components are initialized later with an
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
      PoolComponentMap poolComponents_;      //!< Map of initialized pool components to copy
      ObjectComponentList objectComponents_; //!< List of object component names to add to pool
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////