/* ======================================================================== */
/*!
 * \file            ComponentArrayPopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a component array.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentArrayPopupWidget_BARRAGE_H
#define ComponentArrayPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <string_view>

namespace Barrage
{
  //! Component array right click menu
  class ComponentArrayPopupWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.

        \param strId
          The ID passed to ImGui::OpenPopup() that tells this popup
          when to open.

        \param componentArrayName
          The name of the component being modified.
      */
      /**************************************************************/
      static void Use(const char* strId, const std::string_view& componentArrayName);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentArrayPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////