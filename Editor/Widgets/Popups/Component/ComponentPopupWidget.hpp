/* ======================================================================== */
/*!
 * \file            ComponentPopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a component.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentPopupWidget_BARRAGE_H
#define ComponentPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <string>

namespace Barrage
{
  //! Component right click menu
  class ComponentPopupWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.

        \param strId
          The ID passed to ImGui::OpenPopup() that tells this popup
          when to open.

        \param componentName
          The name of the component being modified.
      */
      /**************************************************************/
      static void Use(const char* strId, const std::string& componentName);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////