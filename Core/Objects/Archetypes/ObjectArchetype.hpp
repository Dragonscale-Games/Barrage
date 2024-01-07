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

#include "Objects/Components/ComponentArray.hpp"
#include "Utilities/Utilities.hpp"

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
      ObjectArchetype(const std::string& name, const StringSet& componentArrayNames = StringSet());

    public:
      std::string name_;                  //!< Name of the object archetype
      ComponentArrayMap componentArrays_; //!< A map of initialized components to copy (each array in this map has only one component)

      friend class Pool;
  };

  using ObjectArchetypeMap = std::map<std::string, ObjectArchetype>;
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////