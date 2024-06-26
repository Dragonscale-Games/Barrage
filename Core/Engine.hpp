/* ======================================================================== */
/*!
 * \file            Engine.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   In charge of setting up engine modules (renderer, input, etc).
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Engine_BARRAGE_H
#define Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Audio/AudioManager.hpp"
#include "Framerate/FramerateController.hpp"
#include "Input/InputManager.hpp"
#include "Renderer/Renderer.hpp"
#include "Scenes/SceneManager.hpp"
#include "Spaces/SpaceManager.hpp"
#include "Window/WindowManager.hpp"

#include "Entry/Entry.hpp"

#include <memory>

namespace Barrage
{
  //! The core engine class for Barrage
  class Engine
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      Engine();
      
      Engine(Engine const&) = delete;
      Engine(Engine&&) = delete;
      Engine& operator=(Engine const&) = delete;
      Engine& operator=(Engine&&) = delete;
      
      /**************************************************************/
      /*!
        \brief
          Gets the instance of the currently running engine.

        \return
          Returns a reference to the engine instance.
      */
      /**************************************************************/
      static Engine& Get();

      /**************************************************************/
      /*!
        \brief
          Initializes the engine and all its modules.
      */
      /**************************************************************/
      void Initialize();

      /**************************************************************/
      /*!
        \brief
          Sets the initial conditions of a game (spaces, scenes,
          loaded assets, etc).

        \param entry
          Holds the information needed to initialize the game.
      */
      /**************************************************************/
      void SetUpGame(Entry& entry);

      /**************************************************************/
      /*!
        \brief
          Shuts down the engine and all its modules.
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's audio manager.

        \return
          Returns a reference to the engine's audio manager.
      */
      /**************************************************************/
      AudioManager& Audio();

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
      /**************************************************************/
      /*!
        \brief
          Used to resize the renderer's framebuffer when the window
          size changes.

        \param window
          Pointer to the active window.

        \param width
          The new width of the window.

        \param height
          The new height of the window.
      */
      /**************************************************************/
      static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    private:
      AudioManager audioManager_;
      FramerateController framerateController_;
      InputManager inputManager_;
      Renderer renderer_;
      SceneManager sceneManager_;
      SpaceManager spaceManager_;
      WindowManager windowManager_;

      static Engine* instance_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////