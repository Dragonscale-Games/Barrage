/* ======================================================================== */
/*!
 * \file            GSMetaballs.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GSMetaballs_BARRAGE_H
#define GSMetaballs_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <GameStates/GameState.hpp>

#include <Objects/Components/EngineComponents.hpp>

namespace Barrage
{
	//! <description>
  class GSMetaballs : public GameState
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Sets the three gamestate functions to the static Enter,
          Update, and Exit functions below.
      */
      /**************************************************************/
      GSMetaballs();

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

      static void CalculateGridValues();

      static void CalculateCellValues();

      static void CreateMesh();

      static void DrawMesh();
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GS_GSMetaballs_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////