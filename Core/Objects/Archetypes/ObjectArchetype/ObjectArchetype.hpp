/* ======================================================================== */
/*!
 * \file            ObjectArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize new objects by copying the values in its component map.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectArchetype_BARRAGE_H
#define ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/EngineComponents.hpp"

namespace Barrage
{
	//! Used to initialize an object
  class ObjectArchetype
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes the archetype with an empty map of components.
      */
      /**************************************************************/
      ObjectArchetype();

      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to object archetype.
      */
      /**************************************************************/
      ~ObjectArchetype();

    public:
      ComponentArrayMap components_; //!< A map of initialized components to copy (each array has only one component)
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////