/* ========================================================================= */
/*!
 *
 * \file            Main.cpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu
 
 * \brief
 * Defines the entry point for the game, staring the systems and
 * letting it go.
 */
/* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================

#include "Game/Game.hpp"

/******************************************************************************/
/*!
  \brief
    Defines the entry point for the application.
*/
/******************************************************************************/

int main(void)
{
  Barrage::Game* game = new Barrage::Game;

  game->Run();

  delete game;

  return 0;
}
