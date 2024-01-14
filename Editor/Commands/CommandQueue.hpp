/* ======================================================================== */
/*!
 * \file            CommandQueue.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows editor commands to be queued, executed at a safe time, and have
   undo/redo functionality.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CommandQueue_BARRAGE_H
#define CommandQueue_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Command.hpp"

#include <stack>
#include <memory>

namespace Barrage
{
  //! Command processor class
  class CommandQueue
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      CommandQueue();

      /**************************************************************/
      /*!
        \brief
          Sends a command to the queue. Sending multiple commands in a
          single frame should be avoided. Only the first command sent
          each frame will be kept; the rest will be discarded.

        \param command
          Shared pointer to command object.
      */
      /**************************************************************/
      void Send(std::shared_ptr<Command> command);

      /**************************************************************/
      /*!
        \brief
          Processes the latest command in the queue (if one exists).
      */
      /**************************************************************/
      void Process();

      /**************************************************************/
      /*!
        \brief
          Undoes the most recent command. If multiple commands are 
          "chained", undoes the entire chain. 
          (See Command.hpp constructor for explanation of chaining.)

        \param log
          If "true", outputs the undo action to the log.
      */
      /**************************************************************/
      void Undo(bool log = true);

      /**************************************************************/
      /*!
        \brief
          Re-executes the most recently undone command. If multiple
          commands are "chained", re-executes the entire chain.
          (See Command.hpp for explanation of chaining.)

        \param log
          If "true", outputs the redo action to the log.
      */
      /**************************************************************/
      void Redo(bool log = true);

      /**************************************************************/
      /*!
        \brief
          Indicates whether there are undo actions the user can take.

        \return
          Returns true if a command that can be undone exists, returns
          false otherwise.
      */
      /**************************************************************/
      bool UndoAvailable();

      /**************************************************************/
      /*!
        \brief
          Indicates whether there are redo actions the user can take.

        \return
          Returns true if a command that can be redone exists, returns
          false otherwise.
      */
      /**************************************************************/
      bool RedoAvailable();

      /**************************************************************/
      /*!
        \brief
          Clears current command in queue, undo stack, and redo
          stack.
      */
      /**************************************************************/
      void Clear();

    private:
      /**************************************************************/
      /*!
        \brief
          Tells editor that scene needs to be updated and project
          has changed since last save.
      */
      /**************************************************************/
      void SetSceneAndProjectDirty();
      
      /**************************************************************/
      /*!
        \brief
          Undoes the most recent command.

        \param log
          If "true", outputs the undo action to the log.
      */
      /**************************************************************/
      void UndoInternal(bool log);

      /**************************************************************/
      /*!
        \brief
          Re-executes the most recently undone command.

        \param log
          If "true", outputs the redo action to the log.

        \return
          Returns true if another command should be redone (used for 
          redo chains).
      */
      /**************************************************************/
      bool RedoInternal(bool log);

      /**************************************************************/
      /*!
        \brief
          Clears all commands from the undo stack and deallocates
          them.
      */
      /**************************************************************/
      void ClearUndoStack();
      
      /**************************************************************/
      /*!
        \brief
          Clears all commands from the redo stack and deallocates
          them.
      */
      /**************************************************************/
      void ClearRedoStack();

    private:
      std::shared_ptr<Command> currentCommand_;        //!< Commands added to the queue are stored here until execution
      std::stack<std::shared_ptr<Command>> undoStack_; //!< Stores all previously executed commands
      std::stack<std::shared_ptr<Command>> redoStack_; //!< Stores all previously undone commands (clears when a new command is processed)
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CommandQueue_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////