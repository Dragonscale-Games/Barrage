/* ======================================================================== */
/*!
 * \file            ComponentWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit the values of a component.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentWidget_BARRAGE_H
#define ComponentWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <Objects/Components/BaseClasses/ComponentArray.hpp>
#include <Objects/Components/BaseClasses/SharedComponent.hpp>

namespace Barrage
{
  //! Allows user to edit the values of a component
  class ComponentWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds a widget to the window that allows the user to edit
          a Barrage component.

        \param componentName
          The name of the component.

        \param component
          The component being edited.

        \return
          Returns true if the component's value changed, returns false
          otherwise.
      */
      /**************************************************************/
      static void Use();

    private:
      /**************************************************************/
      /*!
        \brief
          Used to edit a Barrage component array on an object archetype.
          Only edits the first value of the array.

        \param componentName
          The name of the component.

        \param component
          The component being edited.

        \return
          Returns true if the component's value changed, returns false
          otherwise.
      */
      /**************************************************************/
      static void EditComponentArray(const std::string_view& componentName, ComponentArray* componentArray);

      /**************************************************************/
      /*!
        \brief
          Used to edit a Barrage shared component on a pool archetype.

        \param componentName
          The name of the component.

        \param component
          The component being edited.

        \return
          Returns true if the component's value changed, returns false
          otherwise.
      */
      /**************************************************************/
      static void EditSharedComponent(const std::string_view& componentName, SharedComponent* component);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////