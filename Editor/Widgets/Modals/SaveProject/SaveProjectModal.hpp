/* ======================================================================== */
/*!
 * \file            SaveProjectModal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The "Save project before closing?" popup window.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SaveProjectModal_BARRAGE_H
#define SaveProjectModal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{
  //! "Save project before closing?" popup window
  class SaveProjectModal
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.

        \param strId
          The ID passed to ImGui::OpenPopup() that tells this modal
          when to open.
      */
      /**************************************************************/
      static void Use(const char* strId);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SaveProjectModal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////