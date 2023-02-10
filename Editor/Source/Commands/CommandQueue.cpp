/* ======================================================================== */
/*!
 * \file            CommandQueue.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows editor commands to be queued, executed at a safe time, and have
   undo/redo functionality.
 */
 /* ======================================================================== */

#include "CommandQueue.hpp"
#include <stdexcept>
#include "Editor/Editor.hpp"

namespace Barrage
{
  CommandQueue::CommandQueue() :
    currentCommand_(nullptr),
    undoStack_(),
    redoStack_()
  {
  }

  CommandQueue::~CommandQueue()
  {
    delete currentCommand_;
    ClearUndoStack();
    ClearRedoStack();
  }

  void CommandQueue::Add(Command* command)
  {
    if (currentCommand_ == nullptr)
    {
      currentCommand_ = command;
    }
    else
    {
      delete command;
    }
  }

  void CommandQueue::Process()
  {
    if (currentCommand_ == nullptr)
    {
      return;
    }

    bool executed = currentCommand_->Execute();

    if (executed)
    {
      ClearRedoStack();
      undoStack_.push(currentCommand_);

      if (!currentCommand_->chains_)
      {
        std::string logMessage = currentCommand_->GetName();
        Editor::Instance->Log().AddLog(logMessage.c_str());
      }
    }
    else
    {
      delete currentCommand_;
    }

    currentCommand_ = nullptr;
  }

  void CommandQueue::Undo(bool log)
  {
    if (undoStack_.empty() || currentCommand_)
    {
      return;
    }

    Command* undoCommand = undoStack_.top();
    undoCommand->Undo();

    undoStack_.pop();
    redoStack_.push(undoCommand);
    
    if (log)
    {
      std::string logMessage = "Undo \"" + undoCommand->GetName() + "\"";
      Editor::Instance->Log().AddLog(logMessage.c_str());
    }

    if (undoStack_.empty())
    {
      return;
    }

    Command* nextCommand = undoStack_.top();

    if (nextCommand->chains_)
    {
      Undo(false);
    }
  }

  void CommandQueue::Redo(bool log)
  {
    if (redoStack_.empty() || currentCommand_)
    {
      return;
    }

    Command* redoCommand = redoStack_.top();
    bool success = redoCommand->Execute();

    /*
      In theory, this failure should never happen. If it does, it's likely due to one of these:
        - A command didn't implement Undo correctly
        - Important project state was changed without using a command
    */
    if (!success)
    {
      ClearRedoStack();
      return;
    }

    redoStack_.pop();
    undoStack_.push(redoCommand);

    if (log)
    {
      std::string logMessage = "Redo \"" + redoCommand->GetName() + "\"";
      Editor::Instance->Log().AddLog(logMessage.c_str());
    }
    
    if (redoCommand->chains_)
    {
      Redo(false);
    }
  }

  void CommandQueue::ClearUndoStack()
  {
    while (!undoStack_.empty())
    {
      delete undoStack_.top();
      undoStack_.pop();
    }
  }

  void CommandQueue::ClearRedoStack()
  {
    while (!redoStack_.empty())
    {
      delete redoStack_.top();
      redoStack_.pop();
    }
  }
}