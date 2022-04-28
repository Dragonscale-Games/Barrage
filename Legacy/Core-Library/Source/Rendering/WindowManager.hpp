/* ======================================================================== */
/*!
 *
 * \file            WindowManager.hpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Defines the windowing system used by the engine.
 * This does not create the rendering context for the window,
 * that is the renderer's job.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef WindowSystem_MODULE_H
#define WindowSystem_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <GLFW/glfw3.h>
#include <string>

namespace Barrage
{
  class WindowManager //! The class that manages the window events.
  {
  public:
    struct WindowData //! The data passed into the window.
    {
      int width_;               //!< The width of the window.
      int height_;              //!< The height of the window.
      bool decorated_;          //!< Whether the window is decorated (has title
                                //!< bars and its buttons).
      std::string title_;       //!< The title bar name.
    };

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
        Unset the instance variable when this object gets deleted.
    */
    /*************************************************************************/
    ~WindowManager();
    /*************************************************************************/
    /*!
      \brief
        Makes a copy of another windowing system although only
        one of them can be accessed through the instance function
        at a time.
      \param other
        The original windowing system the copy is made out of.
    */
    /*************************************************************************/
    WindowManager(const WindowManager& other);
    /*************************************************************************/
    /*!
      \brief
        Assigns and copies the data from one windowing system into another.
        Again, only one windowing system can be accessed through
        the instance function.
      \param other
        The other windowingn system copying the data from.
    */
    /*************************************************************************/
    WindowManager& operator=(const WindowManager& other);

    /*************************************************************************/
    /*!
      \brief
        Initializes the window creation upon the engine's initialization.
      \param settings
        The initial window data needed to create the window.
    */
    /*************************************************************************/
    void Initialize(const WindowData& settings);
    /*************************************************************************/
    /*!
      \brief
        Destroys the window upon the engine's shutdown.
        If this is the first window created through the lifetime
        of the engine, this also cleans up the pointer used
        by the Instance function.
    */
    /*************************************************************************/
    void Shutdown();

    /*************************************************************************/
    /*!
      \brief
        Gets the first window created throughout the lifetime of the engine.
    */
    /*************************************************************************/
    static WindowManager* Instance();

    /*************************************************************************/
    /*!
      \brief
        Changes the window settings accordingly to position
        and resize the window to fullscreen.
    */
    /*************************************************************************/
    void ResizeToFullscreen();
    /*************************************************************************/
    /*!
      \brief
        Helper function that sets the window settings such that the width
        and height are 3/4 of the dimensions of the dimensions found
        on the monitor the window is currently and decorates the window.
    */
    /*************************************************************************/
    void ResizeToWindowed();
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
        Resizes the window to the specified width and height.
      \param width
        The new width of the window.
      \param height
        The new height of the window.
    */
    /*************************************************************************/
    void Resize(int width, int height);
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
    void ChangeDecoration(bool decorated);
    /*************************************************************************/
    /*!
      \brief
        Changes the specified title of the window to the one provided.
      \param title
        The new title of the window.
    */
    /*************************************************************************/
    void ChangeTitle(const std::string& title);
    /*************************************************************************/
    /*!
      \brief
        Changes the window according to the specified settings.
      \param data
        The new window data to change the window to.
    */
    /*************************************************************************/
    void Change(const WindowData& data);
    /*************************************************************************/
    /*!
      \brief
        Deletes a previous instance of the window if it exists
        and creates a new one using the specified settings
      \param settings
        The window settings to create the new window with.
    */
    /*************************************************************************/
    void MakeWindow(const WindowData& settings);

    /*************************************************************************/
    /*!
      \brief
        Checks if this is the one the user is currently active.
      \returns
        - True if the window is the one beingn used.
        - False otherwise.
    */
    /*************************************************************************/
    bool IsFocused() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the window's current settings.
      \returns
        The constant reference to the window systems' internal settings.
    */
    /*************************************************************************/
    const WindowData& GetSettings() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the interal pointer handle to the window.
        This should not be used frequently for safety reasons.
        Other libraries might want to access the handle to the windoww.
      \returns
        The internal handle to the GLFW window this class manages.
    */
    /*************************************************************************/
    GLFWwindow* GetInternalHandle();
    /*************************************************************************/
    /*!
      \brief
        Gets the interal pointer handle to the window.
        This should not be used frequently for safety reasons.
        Other libraries might want to access the handle to the window.
      \returns
        The internal handle to the GLFW window this class manages.
    */
    /*************************************************************************/
    const GLFWwindow* GetInternalHandle() const;

  private:
    static WindowManager* instance_; //!< The first instance of the window created.
    GLFWwindow* window_;            //!< The internal handle to the windowing library.
    WindowData data_;               //!< The data given to the window.

    /*************************************************************************/
    /*!
      \brief
        Gets the monitor that currently houses the window.
      \returns
        A pointer to the internal GLFW pointer to the monitor.
    */
    /*************************************************************************/
    const GLFWmonitor* GetParentMonitor() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the monitor that currently houses the window.
      \returns
        A pointer to the internal GLFW pointer to the monitor.
    */
    /*************************************************************************/
    GLFWmonitor* GetParentMonitor();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // WindowSystem_MODULE_H
////////////////////////////////////////////////////////////////////////////////

