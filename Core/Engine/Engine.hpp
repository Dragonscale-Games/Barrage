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
#include "TempRenderer/TestRenderer.hpp"
#include "Random/Random.hpp"

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
      GameStateManager& GSM();

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
      InputManager& Input();

      // ===================================================================
      // Object Manager
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Gets the engine's input manager.

        \return
          Returns a reference to the engine's input manager.
      */
      /**************************************************************/
      ObjectManager& Objects();

      // ===================================================================
      // Random Number Generator
      // ===================================================================

      /**************************************************************/
      /*!
        \brief
          Gets the engine's random number generator.

        \return
          Returns a reference to the engine's random number generator.
      */
      /**************************************************************/
      Random& RNG();

    private:
      GameStateManager gsManager_;  //!< Game state manager
      InputManager inputManager_;   //!< Input manager
      ObjectManager objectManager_; //!< Object manager
      Random rng_;                  //!< Random number generator
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////