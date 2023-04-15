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

#include <Objects/Components/BaseClasses/ComponentArray.hpp>

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
      ObjectArchetype(const std::string& name);

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
          Deep copies a component array map from "other" to "this".

        \param other
          The map to copy.
      */
      /**************************************************************/
      void CopyComponentArrayMap(const ComponentArrayMap& other);

      /**************************************************************/
      /*!
        \brief
          Deep deletes this object's component array map.
      */
      /**************************************************************/
      void DeleteComponentArrayMap();

    public:
      std::string name_;                  //!< A name for an object created with this archetype (for debug purposes, as objects don't have names)
      ComponentArrayMap componentArrays_; //!< A map of initialized components to copy (each array has only one component)
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////