/* ======================================================================== */
/*!
 * \file            ObjectPopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click an object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectPopupWidget_BARRAGE_H
#define ObjectPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include "Widgets/Popups/PopupWidget.hpp"

namespace Barrage
{   
  //! Object right click menu
  class ObjectPopupWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.

        \param strId
          The ID passed to ImGui::OpenPopup() that tells this popup
          when to open.

        \param callback
          A function to be called when the popup closes.
      */
      /**************************************************************/
      static void Use(const char* strId);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////