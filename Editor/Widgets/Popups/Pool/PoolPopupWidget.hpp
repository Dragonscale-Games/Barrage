/* ======================================================================== */
/*!
 * \file            PoolPopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a pool.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolPopupWidget_BARRAGE_H
#define PoolPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{
  //! Pool right click menu
  class PoolPopupWidget
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
#endif // PoolPopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////