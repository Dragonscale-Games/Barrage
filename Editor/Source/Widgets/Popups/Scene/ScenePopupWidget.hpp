/* ======================================================================== */
/*!
 * \file            ScenePopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ScenePopupWidget_BARRAGE_H
#define ScenePopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include "Widgets/Popups/PopupWidget.hpp"

namespace Barrage
{
  //! Scene right click menu
  class ScenePopupWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.

        \param strId
          The ID passed to ImGui::OpenPopup() that tells this popup
          when to open.
      */
      /**************************************************************/
      static void Use(const char* strId);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ScenePopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////