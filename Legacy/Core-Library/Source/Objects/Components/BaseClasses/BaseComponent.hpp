/* ======================================================================== */
/*!
 * \file            BaseComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component class that all component types should inherit from.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef BaseComponent_BARRAGE_H
#define BaseComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <vector>
#include <string>

namespace Barrage
{
  //! Base component class that all component types should inherit from
  class Component
  {
    public:
      //! Type of a given component, so user can get component type from base class pointer
      enum class Type
      {
        OBJECT_COMPONENT,
        POOL_COMPONENT
      };

      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~Component() = default;

      /**************************************************************/
      /*!
        \brief
          Allows user to determine component type from base component
          pointer.

        \return
          Returns component type to identify component.
      */
      /**************************************************************/
      virtual Type GetType() = 0;
  };

  //! Maps component names to allocated components
  typedef std::unordered_map<std::string, Component*> ComponentMap;

  //! Contains a list of names of components
  typedef std::vector<std::string> ComponentList;
}

////////////////////////////////////////////////////////////////////////////////
#endif // BaseComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////