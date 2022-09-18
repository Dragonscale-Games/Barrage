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
#include "SimpleRenderer/SimpleRenderer.hpp"
#include "Spaces/SpaceManager.hpp"

#include "Rendering/GfxDraw2D.hpp"
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
          Gets the engine's drawing module.
        \returns
          Returns a reference to the engine's drawing module.
      */
      /**************************************************************/
      GfxDraw2D& Drawing();
      /**************************************************************/
      /*!
        \brief
          Gets the engine's graphics registry module.
        \returns
          Returns a reference to the engine's registry module.
      */
      /**************************************************************/
      GfxRegistry2D& Registry();

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
          Gets the engine's space manager.

        \return
          Returns a reference to the engine's space manager.
      */
      /**************************************************************/
      SpaceManager& Spaces();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's windowing module.
        \returns
          Returns a reference to the engine's windowing module.
      */
      /**************************************************************/
      WindowManager& Windowing();

    private:
      FramerateController framerateController_; //!< Framerate controller
      InputManager inputManager_;               //!< Input manager
      SpaceManager spaceManager_;               //!< Space manager
      GfxManager2D gfxManager_;
      GfxRenderer2D gfxRenderer_;
      GfxFactory2D gfxFactory_;
      GfxRegistry2D gfxRegistry_;
      GfxDraw2D gfxDrawSystem_;                 //!< The drawing system.
      WindowManager windowManager_;             //!< The windowing manager.
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////