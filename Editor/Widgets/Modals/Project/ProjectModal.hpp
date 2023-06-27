/* ======================================================================== */
/*!
 * \file            ProjectModal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The window that lets the user either create a new project or open an
   existing one.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ProjectModal_BARRAGE_H
#define ProjectModal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <string>

namespace Barrage
{
  //! Project modal
  class ProjectModal
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

      static bool CreateNewProject();

      static bool OpenProject();

    private:
      static bool OpenProjectInternal(std::string projectDirectory);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ProjectModal_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////