/* ======================================================================== */
/*!
 * \file            RenameModal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A selection window that pops up when the user tries to rename something.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RenameModal_BARRAGE_H
#define RenameModal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <string>

namespace Barrage
{
  typedef void (*RenameCallback)(const std::string& newName);
  
  //! Renaming modal
  class RenameModal
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.

        \param strId
          The ID passed to ImGui::OpenPopup() that tells this modal
          when to open.

        \param callback
          The function to call when a user finishes entering a new
          name.
      */
      /**************************************************************/
      static void Use(const char* strId, RenameCallback callback);

    private:
      static std::string newName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RenameModal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////