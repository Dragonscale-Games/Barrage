/* ======================================================================== */
/*!
 * \file            SharedComponentWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit the values of a shared component.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SharedComponentWidget_BARRAGE_H
#define SharedComponentWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <Objects/Components/BaseClasses/SharedComponent.hpp>
#include <string_view>

namespace Barrage
{
  //! Allows user to edit the values of a shared component
  class SharedComponentWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds a widget to the window that allows the user to edit
          a shared component.

        \param componentName
          The name of the shared component.

        \param sharedComponent
          The shared component being edited.

        \return
          Returns true if the shared component's value changed, returns
          false otherwise.
      */
      /**************************************************************/
      static void Use(const std::string_view& componentName, SharedComponent* sharedComponent);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SharedComponentWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////