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

#include "Widgets/Widget.hpp"

namespace Barrage
{
  //! Main menu bar at top of screen
  class MainMenuWidget : public Widget
  {
  public:
    /**************************************************************/
      /*!
        \brief
          Constructs the main menu widget with references to the
          data it's allowed to see/change in the editor and engine.

        \param editorData
          Runtime settings and data for the editor.

        \param engine
          The currently running engine.
      */
    /**************************************************************/
    MainMenuWidget(EditorData& editorData, Engine& engine);

    /**************************************************************/
    /*!
      \brief
        Adds the widget to the window.
    */
    /**************************************************************/
    void UseWidget();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // MainMenuWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////