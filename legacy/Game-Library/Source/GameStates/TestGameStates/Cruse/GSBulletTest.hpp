/* ======================================================================== */
/*!
 * \file            GSBulletTest.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef GSBulletTest_BARRAGE_H
#define GSBulletTest_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <GameStates/GameState.hpp>
#include <Objects/ObjectManager.hpp>

namespace Barrage
{
  //! <description>
  class GSBulletTest : public GameState
  {
  public:
    /**************************************************************/
    /*!
      \brief
        Sets the three gamestate functions to the static Enter,
        Update, and Exit functions below.
    */
    /**************************************************************/
    GSBulletTest();

    static unsigned GetNumBullets();

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
    static unsigned* numBullets_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GSBulletTest_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////