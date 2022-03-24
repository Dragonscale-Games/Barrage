/* ======================================================================== */
/*!
 * \file            Game.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Uses Barrage Engine and a game library to run a game project.

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Game_BARRAGE_H
#define Game_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Engine/Engine.hpp>

namespace Barrage
{
	//! Runs a Barrage game project
  class Game
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      Game();
      
      /**************************************************************/
      /*!
        \brief
          Runs the game project.
      */
      /**************************************************************/
      void Run();

    private:
      /**************************************************************/
      /*!
        \brief
          Initializes Barrage engine and game systems.
      */
      /**************************************************************/
      void Initialize();

      /**************************************************************/
      /*!
        \brief
          Updates main game loop.
      */
      /**************************************************************/
      void Update();

      /**************************************************************/
      /*!
        \brief
          Shuts down Barrage engine and game systems.
      */
      /**************************************************************/
      void Shutdown();

    private:
      Engine engine_;  //!< Barrage engine
      bool isRunning_; //!< Keeps track of whether game is running
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Game_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////