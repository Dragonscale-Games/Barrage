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
#include <Objects/Components/Component.hpp>
#include <string>

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
          a component.

        \param componentName
          The name of the component.

        \param component
          The component being edited.

        \return
          Returns true if the component's value changed, returns
          false otherwise.
      */
      /**************************************************************/
      static void Use(const std::string& componentName, ComponentDeepPtr& component);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////