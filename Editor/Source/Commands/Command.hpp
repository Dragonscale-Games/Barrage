/* ======================================================================== */
/*!
 * \file            Command.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base class for editor commands. A command should be used for anything that 
   changes the state of the editor project.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Command_BARRAGE_H
#define Command_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>

namespace Barrage
{
  //! Command base class
  class Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Command base class constructor.

        \param message
          The message that will be displayed to the log window when
          this command is executed.

        \param chainUndo
          Allows multiple commands to be undone at once. Also applies to
          redo. 
          
          Here's how it works. Imagine the five most recent commands were:

          (oldest)
          - Change String Value
          - Change Color
          - Change Position Value (chainUndo)
          - Change Position Value (chainUndo)
          - Change Position Value
          (most recent)

          Let's say the user performs an Undo action (like pressing
          Ctrl + Z). First, the most recent command is undone (always). 
          In this case, that's the bottom "Change Position Value". Then 
          the next most recent command is checked. If "chainUndo" is true, 
          that command will also be undone. This continues until a
          command with "chainUndo" set to false is found. In the case
          above, this means the three "Change Position Value" commands
          will all be undone.

          This can be useful for things that make lots of small changes
          to the project state, like dragging an object with the mouse
          or using widgets with continuous editing. Instead of having
          a bunch of tiny changes each need their own Undo action, they
          can be combined into one.

          IMPORTANT: A series of "chainUndo" commands should end with 
          a command where "chainUndo" is set to false. 
      */
      /**************************************************************/
      Command(const std::string& message, bool chainUndo = false);

      /**************************************************************/
      /*!
        \brief
          Virtual destructor for base class.
      */
      /**************************************************************/
      virtual ~Command() = default;

    protected:
      /**************************************************************/
      /*!
        \brief
          Gets the command's execution message.

        \return
          Returns the command's execution message.
      */
      /**************************************************************/
      std::string GetMessage();

      /**************************************************************/
      /*!
        \brief
          Executes the command.

        \return
          Returns true if the command successfully executed. False
          should be returned only if the command had no effect.
      */
      /**************************************************************/
      virtual bool Execute() = 0;

      /**************************************************************/
      /*!
        \brief
          This function should completely reverse the effect of the
          Execute() function. You can assume it will only be called 
          directly after a successful Execute() call (one that returned 
          "true").
      */
      /**************************************************************/
      virtual void Undo() = 0;

      /**************************************************************/
      /*!
        \brief
          This function should completely reverse the effect of the
          Undo() function. You can assume it will only be called
          directly after Undo() is called. 

          This function will often look similar to Execute(), and it
          may be the same in some cases.
      */
      /**************************************************************/
      virtual void Redo() = 0;

    protected:
      std::string message_; //!< message shown in the log window when the command executes
      bool chains_;         //!< tracks whether the command "chains" during an undo (see constructor for explanation)

    friend class CommandQueue;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Command_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////