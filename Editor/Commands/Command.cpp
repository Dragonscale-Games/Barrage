/* ======================================================================== */
/*!
 * \file            Command.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base class for editor commands. Commands are for things like editing a value,
   deleting an object, and other editor actions. This class allows these actions
   to be queued and have undo/redo functionality.
 */
 /* ======================================================================== */

#include "Command.hpp"

namespace Barrage
{
  Command::Command(const std::string& message, bool chainUndo) :
    message_(message),
    chains_(chainUndo)
  {
  }

  std::string Command::GetMessage()
  {
    return message_;
  }
}