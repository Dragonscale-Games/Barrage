/* ======================================================================== */
/*!
 * \file            BaseComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component class that all components should inherit from.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef BaseComponent_BARRAGE_H
#define BaseComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
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
        SHARED,
        ARRAY
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

      /**************************************************************/
      /*!
        \brief
          Allows user to determine the name of the component's child
          class (for use with reflection).

        \return
          Returns the name of the component's child class.
      */
      /**************************************************************/
      virtual std::string GetClassName() = 0;
  };

  //! Associates components with their names
  typedef std::unordered_map<std::string, Component*> ComponentMap;
}

////////////////////////////////////////////////////////////////////////////////
#endif // BaseComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////