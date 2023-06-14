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
#include <string>

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

      static ImVec2 GetSize();

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

        \param text
          A printf()-style formatted C string.
      */
      /**************************************************************/
      static void AddEntry(const char* text, ...) IM_FMTARGS(2);
      
      /**************************************************************/
      /*!
        \brief
          Adds an entry to the log.

        \param text
          The text to add as a std::string.
      */
      /**************************************************************/
      static void AddEntry(const std::string& text);

    private:
      static ImGuiTextBuffer buffer_;
      static ImGuiTextFilter filter_;
      static ImVector<int> lineOffsets_;
      static bool scrollToBottom_;
      static ImVec2 size_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // LogWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////