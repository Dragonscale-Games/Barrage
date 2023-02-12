/* ======================================================================== */
/*!
 * \file            LogWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for displaying a log window. Code taken from imgui_demo.cpp.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef LogWidget_BARRAGE_H
#define LogWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>

namespace Barrage
{
  //! Displays a log window
  class LogWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      static void Use();

      /**************************************************************/
      /*!
        \brief
          Clears the log window.
      */
      /**************************************************************/
      static void Clear();

      /**************************************************************/
      /*!
        \brief
          Adds an entry to the log.

        \param fmt
          A printf()-style formatted C string.
      */
      /**************************************************************/
      static void AddEntry(const char* fmt, ...) IM_FMTARGS(2);

    private:
      static ImGuiTextBuffer buffer_;
      static ImGuiTextFilter filter_;
      static ImVector<int> lineOffsets_;
      static bool scrollToBottom_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // LogWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////