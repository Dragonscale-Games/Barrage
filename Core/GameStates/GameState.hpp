/* ======================================================================== */
/*!
 * \file            GameState.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base game state class. To create a custom game state:
     1. Create a class that's derived from GameState.
     2. Create up to three static member functions:
        static void Enter(); (optional)
        static void Update();
        static void Exit();  (optional)
     3. Create a default constructor for the custom game state class with no 
        parameters, and set the class's enter_, update_, and exit_ fields to 
        the corresponding static functions. The enter_ and exit_ fields may
        be set to nullptr.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef GameState_BARRAGE_H
#define GameState_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  typedef void (*GSFunc)(void);
  
  //! Base game state class. 
  class GameState
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Constructor for GameState object. A gamestate consists of
          up to three basic functions:

        \param enter
          The enter function is called once when the gamestate is
          entered. It is optional and may be set to nullptr.

        \param update
          The update function is called once per frame. This function
          must be provided.

        \param exit
          The exit function is called once when the gamestate is
          exited. It is optional and may be set to nullptr.
      */
      /**************************************************************/
      GameState(GSFunc enter, GSFunc update, GSFunc exit);

      virtual ~GameState() = default;

      /**************************************************************/
      /*!
        \brief
          Evaluates whether two game states are equal. Two game states
          are equal if they have exactly the same enter, update, and
          exit functions.

        \param rhs
          The game state on the right side of the operator.

        \return
          Returns true if the game states are equal and false otherwise.
      */
      /**************************************************************/
      bool operator==(const GameState& rhs) const;

      /**************************************************************/
      /*!
        \brief
          Evaluates whether two game states are not equal. See above
          for definition of game state equality.

        \param rhs
          The game state on the right side of the operator.

        \return
          Returns true if the game states aren't equal and false 
          otherwise.
      */
      /**************************************************************/
      bool operator!=(const GameState& rhs) const;

    private:
      GSFunc enter_;  //!< Pointer to enter function for the game state
      GSFunc update_; //!< Pointer to update function for the game state
      GSFunc exit_;   //!< Pointer to exit function for the game state

    friend class GameStateManager;
    friend class Engine;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // GameState_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////