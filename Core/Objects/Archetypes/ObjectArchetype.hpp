/* ======================================================================== */
/*!
 * \file            ObjectArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Used to initialize the values of new objects.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectArchetype_BARRAGE_H
#define ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Components/ComponentArray.hpp>

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
      ObjectArchetype(const std::string& name, const std::vector<std::string>& componentArrayNames = std::vector<std::string>());

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

    private:
      std::string name_;                  //!< A name for an object created with this archetype (for debug/editor purposes, as objects don't have names)
      ComponentArrayMap componentArrays_; //!< A map of initialized components to copy (each array in this map has only one component)
  };

  using ObjectArchetypeMap = std::map<std::string, ObjectArchetype>;
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////