/* ======================================================================== */
/*!
 * \file            Engine.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The core engine class for a Barrage bullet hell game. Running this runs 
   the game.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_BARRAGE_H
#define Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "FramerateController/FramerateController.hpp"
#include "Input/InputManager.hpp"
#include "Renderer/Renderer.hpp"
#include "Spaces/SpaceManager.hpp"
#include "Scenes/SceneManager.hpp"
#include "Window/WindowManager.hpp"

#include "Entry/Entry.hpp"
#include "Utilities/Logger.hpp"

namespace Barrage
{   
  //! The core engine class for a Barrage bullet hell game
  class Engine
	{
    public:   
      static Engine* Instance;

      /**************************************************************/
      /*!
        \brief
          Initializes the engine and all its subsystems.
      */
      /**************************************************************/
      void Initialize();

      /**************************************************************/
      /*!
        \brief
          Sets the initial conditions of a game (spaces, scenes, 
          loaded assets, etc).
      */
      /**************************************************************/
      void SetUpGame(Entry& entry);

      /**************************************************************/
      /*!
        \brief
          Shuts down the engine and all its subsystems.
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's framerate controller.

        \return
          Returns a reference to the engine's framerate controller.
      */
      /**************************************************************/
      FramerateController& Frames();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's renderer.

        \return
          Returns a reference to the engine's renderer.
      */
      /**************************************************************/
      Renderer& Graphics();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's input manager.

        \return
          Returns a reference to the engine's input manager.
      */
      /**************************************************************/
      InputManager& Input();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's scene manager.

        \return
          Returns a reference to the engine's scene manager.
      */
      /**************************************************************/
      SceneManager& Scenes();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's space manager.

        \return
          Returns a reference to the engine's space manager.
      */
      /**************************************************************/
      SpaceManager& Spaces();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's window manager.

        \return
          Returns a reference to the engine's window manager.
      */
      /**************************************************************/
      WindowManager& Window();

    private:
      FramerateController framerateController_; 
      InputManager inputManager_; 
      Renderer renderer_;
      SceneManager sceneManager_; 
      SpaceManager spaceManager_;
      WindowManager windowManager_;

      static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////