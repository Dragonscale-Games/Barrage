/* ======================================================================== */
/*!
 * \file            TimelineWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for displaying the game timeline.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef TimelineWidget_BARRAGE_H
#define TimelineWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{
  //! Displays a log window
  class TimelineWidget
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
#endif // TimelineWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////