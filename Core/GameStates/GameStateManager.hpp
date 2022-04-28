/* ======================================================================== */
/*!
 * \file            GameStateManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages the current game state.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GameStateManager_BARRAGE_H
#define GameStateManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "GameState.hpp"

namespace Barrage
{
  //! Manages the current game state.
  class GameStateManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor. Sets "current" and "next" gamestates
          to empty.
      */
      /**************************************************************/
      GameStateManager();
      
      /**************************************************************/
      /*!
        \brief
          Sets the next game state of the manager.

          Game state changes at the beginning of the manager's next
          update loop.

          This function initializes the manager if no game state is
          currently running.

          If this function is called with a game state that's already
          running, that game state will restart.

        \param state
          The custom game state to change to.
      */
      /**************************************************************/
      void SetGameState(GameState state);

      /**************************************************************/
      /*!
        \brief
          Should be called whenever the simulation needs to be updated.
          Does not use dt as a parameter; size of time step should be
          fixed.
      */
      /**************************************************************/
      void Update();

      /**************************************************************/
      /*!
        \brief
          If a game state is running, exits it and removes it from
          the game state manager.
      */
      /**************************************************************/
      void QuitGameState();
      
      /**************************************************************/
      /*!
        \brief
          To be called by the engine. 
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Evaluates whether a game state is currently running.

        \return
          Returns true if game state is changing and returns false
          otherwise.
      */
      /**************************************************************/
      bool GameStateIsRunning();

    private:
      /**************************************************************/
      /*!
        \brief
          Evaluates whether a game state change has been queued.

        \return
          Returns true if game state is changing and returns false
          otherwise.
      */
      /**************************************************************/
      bool GameStateIsChanging() const;

      /**************************************************************/
      /*!
        \brief
          Evaluates whether a game state restart has been queued.

        \return
          Returns true if game state is restarting and returns false 
          otherwise.
      */
      /**************************************************************/
      bool GameStateIsRestarting() const;
    
    private:
      GameState current_;   //!< The currently running game state.
      GameState next_;      //!< The next game state to run.

      bool stateIsRunning_; //!< Keeps track of whether a game state is currently running
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GameStateManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////