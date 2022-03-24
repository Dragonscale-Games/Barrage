/* ======================================================================== */
/*!
 * \file            GSEntry.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Initial game state for the engine.

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GSEntry_BARRAGE_H
#define GSEntry_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <GameStates/GameState.hpp>

namespace Barrage
{
	//! Initial game state for the engine
  class GSEntry : public GameState
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Sets the three gamestate functions to the static Enter,
          Update, and Exit functions below.
      */
      /**************************************************************/
      GSEntry();

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
      static int cursorPosition_; //!< Position of the game state selection cursor
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GSEntry_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////