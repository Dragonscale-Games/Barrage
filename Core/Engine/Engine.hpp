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
          Shuts down the engine and all its subsystems.
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's frame rate controller.

        \return
          Returns a reference to the engine's frame rate controller.
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

    private:
      FramerateController framerateController_; 
      InputManager inputManager_; 
      Renderer renderer_;
      SceneManager sceneManager_; 
      SpaceManager spaceManager_; 
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////