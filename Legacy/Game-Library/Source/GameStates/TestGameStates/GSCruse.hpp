/* ======================================================================== */
/*!
 * \file            GSCruse.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GSCruse_BARRAGE_H
#define GSCruse_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <GameStates/GameState.hpp>

namespace Barrage
{
	//! <description>
  class GSCruse : public GameState
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Sets the three gamestate functions to the static Enter,
          Update, and Exit functions below.
      */
      /**************************************************************/
      GSCruse();

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
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GS_STUB_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////