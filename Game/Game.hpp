/* ======================================================================== */
/*!
 * \file            Game.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Standard game loop for Barrage Engine.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Game_BARRAGE_H
#define Game_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Engine/Engine.hpp>

namespace Barrage
{
  //! Standard game loop for Barrage Engine
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
          Runs the game.
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

      /**************************************************************/
      /*!
        \brief
          Uses the entry file to set up the initial state of the 
          game.
      */
      /**************************************************************/
      void ParseEntryFile();

    private:
      Engine engine_;  //!< Barrage engine
      bool isRunning_; //!< Keeps track of whether game is running
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Game_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////