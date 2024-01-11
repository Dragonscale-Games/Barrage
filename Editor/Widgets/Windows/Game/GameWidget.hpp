/* ======================================================================== */
/*!
 * \file            GameWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Displays the current game scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GameWidget_BARRAGE_H
#define GameWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{
  //! Displays the current game scene
  class GameWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      static void Use();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GameWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////