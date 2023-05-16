/* ======================================================================== */
/*!
 * \file            SharedComponentPopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a shared component.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SharedComponentPopupWidget_BARRAGE_H
#define SharedComponentPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <string_view>

namespace Barrage
{
  //! Shared component right click menu
  class SharedComponentPopupWidget
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
      static void Use(const char* strId, const std::string_view& componentName);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SharedComponentPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////