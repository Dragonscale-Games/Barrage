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
          Copy constructor.

        \param other
          The archetype to copy.
      */
      /**************************************************************/
      ObjectArchetype(const ObjectArchetype& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator.

        \param other
          The archetype to copy.
      */
      /**************************************************************/
      ObjectArchetype& operator=(const ObjectArchetype& other);

      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to object archetype.
      */
      /**************************************************************/
      ~ObjectArchetype();

    private:
      /**************************************************************/
      /*!
        \brief
          Helper function that copies a component map to this object's
          component map. This object's old component map is deleted 
          first.

        \param other
          The component map to copy.
      */
      /**************************************************************/
      void CopyComponentMap(const ComponentArrayMap& other);

      /**************************************************************/
      /*!
        \brief
          Helper function that delets the component map of this
          object.
      */
      /**************************************************************/
      void DeleteComponentMap();

    public:
      ComponentArrayMap components_; //!< A map of initialized components to copy (each array has only one component)
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////