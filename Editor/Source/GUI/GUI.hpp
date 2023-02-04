/* ======================================================================== */
/*!
 * \file            GUI.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages ImGui and contains all ImGui widgets/user controls for the editor.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GUI_BARRAGE_H
#define GUI_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Barrage
{
	//! ImGui wrapper class
  class GUI
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      GUI();

      /**************************************************************/
      /*!
        \brief
          Creates ImGui context and initializes it.

        \param window
          Handle to the window ImGui will use as its render target.
      */
      /**************************************************************/
      void Initialize(GLFWwindow* window);

      /**************************************************************/
      /*!
        \brief
          Starts a new frame for widget recording. Should be called
          once per editor update, before any widget functions are
          called.
      */
      /**************************************************************/
      void StartWidgets();

      /**************************************************************/
      /*!
        \brief
          Ends the current frame for widget recording. Should be 
          called once per editor update, after all widget functions
          have been called.
      */
      /**************************************************************/
      void EndWidgets();

      /**************************************************************/
      /*!
        \brief
          Renders all widgets recorded during the previous frame.
      */
      /**************************************************************/
      void DrawWidgets();

      /**************************************************************/
      /*!
        \brief
          Shuts down and destroys the ImGui context.
      */
      /**************************************************************/
      void Shutdown();

    private:
      /**************************************************************/
      /*!
        \brief
          Creates a space that allows windows to be docked and
          undocked from the editor.
      */
      /**************************************************************/
      void BeginDockingSpace();

      /**************************************************************/
      /*!
        \brief
          Ends the docking space.
      */
      /**************************************************************/
      void EndDockingSpace();
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GUI_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////