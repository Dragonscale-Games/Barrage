/* ======================================================================== */
/*!
 * \file            Widget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base class for all editor widgets.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Widget_BARRAGE_H
#define Widget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Editor/EditorData.hpp>
#include <Engine/Engine.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Barrage
{
  //! Widget base class
  class Widget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs a widget with references to the data it's allowed
          to see/change in the editor and engine.

        \param editorData
          Runtime settings and data for the editor.

        \param engine
          The currently running engine.
      */
      /**************************************************************/
      Widget(EditorData& editorData, Engine& engine);

      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      virtual void UseWidget() = 0;

    protected:
      EditorData& editorData_; //!< Settings and other runtime data used by the editor
      Engine& engine_;         //!< The currently running engine
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Widget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////