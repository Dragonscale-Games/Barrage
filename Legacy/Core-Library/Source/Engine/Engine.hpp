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

#include "Input/InputManager.hpp"
#include "GameStates/GameStateManager.hpp"
#include "Objects/ObjectManager.hpp"
#include "Rendering/GfxManager2D.hpp"
#include "Rendering/GfxRenderer2D.hpp"
#include "Rendering/WindowManager.hpp"

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
          Default constructor.
      */
      /**************************************************************/
      Engine();

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
          Shuts down the engine and all its subsystems.
      */
      /**************************************************************/
      void Shutdown();

      // ===================================================================
      // Game State Manager
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Gets the engine's gamestate manager.

        \return
          Returns a reference to the engine's gamestate Manager.
      */
      /**************************************************************/
      static GameStateManager& GSM();

      // ===================================================================
      // Input Manager
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Gets the engine's input manager.

        \return
          Returns a reference to the engine's input manager.
      */
      /**************************************************************/
      static InputManager& Input();

      // ===================================================================
      // Input Manager
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Gets the engine's input manager.

        \return
          Returns a reference to the engine's input manager.
      */
      /**************************************************************/
      static ObjectManager& Objects();

      // ===================================================================
      // Graphics
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Gets the engine's graphics resources manager.

        \return
          Returns a reference to the engine's graphics resource manager.
      */
      /**************************************************************/
      static GfxManager2D& GfxManager();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's main renderer.

        \returns
          A reference to the engine's main renderer.
      */
      /**************************************************************/
      static GfxRenderer2D& GfxRenderer();

      // ===================================================================
      // Windowing
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Gets the engine's window manager.

        \return
          Returns a reference to the engine's window manager.
      */
      /**************************************************************/
      static WindowManager& Window();

      // ===================================================================
      // Non-Singleton Function Deletions
      // ===================================================================

      Engine(Engine& other) = delete;

      void operator=(const Engine& rhs) = delete;

    private:
      GameStateManager* gsManager_;  //!< Game state manager instance
      InputManager* inputManager_;   //!< Input manager instance
      ObjectManager* objectManager_; //!< Object manager instance
      GfxManager2D* gfxManager_;     //!< Graphics resource manager instance
      GfxRenderer2D* gfxRenderer_;   //!< Graphics renderer instance
      WindowManager* windowManager_; //!< Window manager instance
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////