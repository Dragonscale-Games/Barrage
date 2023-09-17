/* ======================================================================== */
/*!
 * \file            InputManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
     Handles input events from GLFW. 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef InputManager_BARRAGE_H
#define InputManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace Barrage
{
  //! Handles input events from GLFW. 
  class InputManager
	{
    public:   
      static const int MIN_KEY_VALUE = GLFW_KEY_UNKNOWN;
      static const int MAX_KEY_VALUE = GLFW_KEY_LAST;
      
      /**************************************************************/
      /*!
        \brief
          Default constructor. Sets window handle to empty and starts
          manager with empty key vectors.
      */
      /**************************************************************/
      InputManager();
      
      /**************************************************************/
      /*!
        \brief
          Initializes the input manager. Sets the window, sets
          up any glfw input callbacks, and initializes the key vectors.

        \param window
          The game window.
      */
      /**************************************************************/
      void Initialize(GLFWwindow* window);

      /**************************************************************/
      /*!
        \brief
          Resets the states of key triggers and releases to prepare
          for a new frame.
      */
      /**************************************************************/
      void Reset();

      /**************************************************************/
      /*!
        \brief
          Removes glfw input callbacks and empties the manager's
          variables.
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Returns true if the given key was pressed this frame
          and returns false otherwise.

        \param key
          The GLFW key to test.

        \return
          Returns true if the key was pressed this frame and
          returns false otherwise.
      */
      /**************************************************************/
      bool KeyTriggered(int key) const;

      /**************************************************************/
      /*!
        \brief
          Returns true if the given key is currently down and returns
          false otherwise.

        \param key
          The key to test. Use the key names from KeyMap.hpp.

        \return
          Returns true if the key is currently down and returns false
          otherwise.
      */
      /**************************************************************/
      bool KeyIsDown(int key) const;

      /**************************************************************/
      /*!
        \brief
          Returns true if the given key was released this frame
          and returns false otherwise.

        \param key
          The GLFW key to test.

        \return
          Returns true if the key was released this frame and
          returns false otherwise.
      */
      /**************************************************************/
      bool KeyReleased(int key) const;

    private:
      /**************************************************************/
      /*!
        \brief
          Checks whether the provided key is valid. Usually used to
          avoid out-of-bounds array access.

        \param key
          The keyboard key to check.

        \return
          Returns true if the key is a valid keycode and false
          otherwise.
      */
      /**************************************************************/
      static bool KeyIsValid(int key);
      
      /**************************************************************/
      /*!
        \brief
          Keyboard callback function for glfw. Is called whenever a
          keyboard key is pressed.

        \param window
          The window that received the event. Unused in this function.

        \param key
          The keyboard key that was pressed or released.

        \param scancode
          The system-specific scancode of the key. Unused in this
          function.

        \param action
          GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT. 

        \param mods
          Bit field describing which modifier keys were held down.
          Unused in this function.
      */
      /**************************************************************/
      static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    private:
      GLFWwindow* window_; //!< Handle to the game window

      std::vector<bool> keyTriggers_; //!< Sparse vector containing which keys have been triggered since last input update
      std::vector<bool> keyReleases_; //!< Sparse vector containing which keys have been released since last input update
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // InputManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////