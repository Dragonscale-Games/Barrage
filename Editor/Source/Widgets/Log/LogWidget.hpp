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

#include "Widgets/Widget.hpp"

namespace Barrage
{
  //! Displays a log window
  class LogWidget : public Widget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the log widget with references to the
          data it's allowed to see/change in the editor and engine.

        \param editorData
          Runtime settings and data for the editor.

        \param engine
          The currently running engine.
      */
      /**************************************************************/
      LogWidget(EditorData& editorData, Engine& engine);

      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      void UseWidget();

      /**************************************************************/
      /*!
        \brief
          Clears the log window.
      */
      /**************************************************************/
      void Clear();

      /**************************************************************/
      /*!
        \brief
          Adds an entry to the log.

        \param fmt
          A printf()-style formatted C string.
      */
      /**************************************************************/
      void AddEntry(const char* fmt, ...) IM_FMTARGS(2);

    private:
      ImGuiTextBuffer buffer_;
      ImGuiTextFilter filter_;
      ImVector<int> lineOffsets_;
      bool scrollToBottom_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // LogWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////