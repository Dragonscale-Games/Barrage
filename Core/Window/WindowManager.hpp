/* ======================================================================== */
/*!
 *
 * \file            WindowManager.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
    Manages the game window.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef WindowManager_MODULE_H
#define WindowManager_MODULE_H
////////////////////////////////////////////////////////////////////////////////

#include <GLFW/glfw3.h>
#include <string>

namespace Barrage
{
  class WindowManager //! Manages the game window.
  {
    public:
      static const int DEFAULT_WIDTH = 1280;
      static const int DEFAULT_HEIGHT = 720;
      
      /*************************************************************************/
      /*!
        \brief
          Creates a single windowing system.
      */
      /*************************************************************************/
      WindowManager();

      /*************************************************************************/
      /*!
        \brief
          Creates the game window.
      */
      /*************************************************************************/
      void Initialize();

      /*************************************************************************/
      /*!
        \brief
          Destroys the game window.
      */
      /*************************************************************************/
      void Shutdown();

      /*************************************************************************/
      /*!
        \brief
          Displays the current back buffer.
      */
      /*************************************************************************/
      void SwapBuffers();
      /*************************************************************************/
      /*!
        \brief
          Polls the system events for this window.
      */
      /*************************************************************************/
      void PollEvents();

      /*************************************************************************/
      /*!
        \brief
          Forces the internal window to become the focused window.
          Brings the window up to the top of a stack of other windows.
      */
      /*************************************************************************/
      void Focus();

      /*************************************************************************/
      /*!
        \brief
          Maximizes the window.
      */
      /*************************************************************************/
      void Maximize();

      /*************************************************************************/
      /*!
        \brief
          Resizes the window to the specified width and height.
        \param width
          The new width of the window.
        \param height
          The new height of the window.
      */
      /*************************************************************************/
      void SetSize(int width, int height);

      /*************************************************************************/
      /*!
        \brief
          Sets whether the window is decorated or not.
        \param decorated
          True if the window is set to be decorated (the titlebar is visible
          along with the buttons).
          False if the window is not (the titlebar is nowhere to be seen).
      */
      /*************************************************************************/
      void SetDecoration(bool decorated);

      /*************************************************************************/
      /*!
        \brief
          Changes the specified title of the window to the one provided.
        \param title
          The new title of the window.
      */
      /*************************************************************************/
      void SetTitle(const char* title);

      /*************************************************************************/
      /*!
        \brief
          Makes the window fullscreen (covers full screen, no decoration).
      */
      /*************************************************************************/
      void SetFullScreen();

      /*************************************************************************/
      /*!
        \brief
          Makes the window windowed (decorated and maximized).
      */
      /*************************************************************************/
      void SetWindowed();

      /*************************************************************************/
      /*!
        \brief
          Checks whether the window is closing or not.
        \returns
          - True if the window is closing, false otherwise.
      */
      /*************************************************************************/
      bool IsClosed() const;
      /*************************************************************************/
      /*!
        \brief
          Checks if the window is currently focused.
        \returns
          - True if the window is the one beingn used.
          - False otherwise.
      */
      /*************************************************************************/
      bool IsFocused() const;

      /*************************************************************************/
      /*!
        \brief
          Gets the window's handle.

        \returns
          Returns a pointer to the GLFW window.
      */
      /*************************************************************************/
      GLFWwindow* GetWindowHandle();

    private:
      GLFWwindow* window_;            //!< The internal handle to the windowing library.

      /*************************************************************************/
      /*!
        \brief
          Creates the glfw window.
      */
      /*************************************************************************/
      void CreateWindow();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // WindowManager_MODULE_H
////////////////////////////////////////////////////////////////////////////////
