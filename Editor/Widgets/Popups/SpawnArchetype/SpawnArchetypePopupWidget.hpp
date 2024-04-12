/* ======================================================================== */
/*!
 * \file            SpawnArchetypePopupWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The menu that pops up when you right click a spawn archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnArchetypePopupWidget_BARRAGE_H
#define SpawnArchetypePopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{   
  //! Spawn archetype right click menu
  class SpawnArchetypePopupWidget
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
#endif // SpawnArchetypePopupWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////