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

#include "KeyMap.hpp"

#include <vector>

struct GLFWwindow;

namespace Barrage
{
  //! Handles input events from GLFW. 
  class InputManager
	{
    public:   
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
          Initializes the game state manager. Sets the window, sets
          up any glfw input callbacks, and initializes the key vectors.

        \param window
          The game window.
      */
      /**************************************************************/
      void Initialize(GLFWwindow* window);

      /**************************************************************/
      /*!
        \brief
          Calls glfwPollEvents and updates the key vectors.
      */
      /**************************************************************/
      void Update();

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
          Returns true if the given key was first pressed this frame
          and returns false otherwise.

        \param key
          The key to test. Use the key names from KeyMap.hpp.

        \return
          Returns true if the key was first pressed this frame and
          returns false otherwise.
      */
      /**************************************************************/
      bool KeyTriggered(KEY key) const;

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
      bool KeyIsDown(KEY key) const;

      /**************************************************************/
      /*!
        \brief
          Returns true if the given key was first released this frame
          and returns false otherwise.

        \param key
          The key to test. Use the key names from KeyMap.hpp.

        \return
          Returns true if the key was first released this frame and
          returns false otherwise.
      */
      /**************************************************************/
      bool KeyReleased(KEY key) const;

    private:
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
      static InputManager* manager_;
      
      GLFWwindow* window_; //!< Handle to the game window

      std::vector<bool> keysPrev_; //!< Sparse vector containing key states from previous frame
      std::vector<bool> keysCurr_; //!< Sparse vector containing key states from current frame
      std::vector<bool> keysBuff_; //!< Sparse vector containing key states being modified in realtime by keyboard callbacks
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // InputManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////