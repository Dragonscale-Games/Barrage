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
#include "SimpleRenderer/SimpleRenderer.hpp"
#include "Spaces/SpaceManager.hpp"

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
          Gets the engine's input manager.

        \return
          Returns a reference to the engine's input manager.
      */
      /**************************************************************/
      InputManager& Input();

      /**************************************************************/
      /*!
        \brief
          Gets the engine's renderer.

        \return
          Returns a reference to the engine's renderer.
      */
      /**************************************************************/
      SimpleRenderer& Render();

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
      InputManager inputManager_;   //!< Input manager
      SimpleRenderer renderer_;     //!< Renderer
      SpaceManager spaceManager_;   //!< Space manager
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Engine_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////