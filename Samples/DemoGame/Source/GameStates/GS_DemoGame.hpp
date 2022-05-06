/* ======================================================================== */
/*!
 * \file            GS_DemoGame.hpp
 * \par             Demo Game
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Demo game state.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GS_DemoGame_DEMO_H
#define GS_DemoGame_DEMO_H
////////////////////////////////////////////////////////////////////////////////

#include <GameStates/GameState.hpp>

namespace Demo
{
	//! <description>
  class GS_DemoGame : public Barrage::GameState
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Sets the three gamestate functions to the static Enter,
          Update, and Exit functions below.
      */
      /**************************************************************/
      GS_DemoGame();

    private:
      /**************************************************************/
      /*!
        \brief
          The enter function is called once when the gamestate is
          entered. It is optional.
      */
      /**************************************************************/
      static void Enter();

      /**************************************************************/
      /*!
        \brief
          The enter function is called once when the gamestate is
          entered. It must be defined.
      */
      /**************************************************************/
      static void Update();

      /**************************************************************/
      /*!
        \brief
          The exit function is called once when the gamestate is
          exited. It is optional.
      */
      /**************************************************************/
      static void Exit();

    private:
      static bool isPaused_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GS_DemoGame_DEMO_H
////////////////////////////////////////////////////////////////////////////////