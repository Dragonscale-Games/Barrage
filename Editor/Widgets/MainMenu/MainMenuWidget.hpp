/* ======================================================================== */
/*!
 * \file            MainMenuWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main menu bar that shows at the top of the screen.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef MainMenuWidget_BARRAGE_H
#define MainMenuWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{
  //! Main menu bar at top of screen
  class MainMenuWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      static void Use();

      static ImVec2 GetSize();

    private:
      static void ImportTexture();

      static ImVec2 size_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // MainMenuWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////