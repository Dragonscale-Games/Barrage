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
#include "Editor.hpp"

namespace Barrage
{
  CommandQueue::CommandQueue() :
    currentCommand_(nullptr),
    undoStack_(),
    redoStack_()
  {
  }

  void CommandQueue::Send(std::shared_ptr<Command> command)
  {
    if (currentCommand_ == nullptr)
    {
      currentCommand_ = command;
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
        std::string logMessage = currentCommand_->GetMessage();
        LogWidget::AddEntry(logMessage.c_str());
      }
    }
    else
    {
      std::string logMessage = "Failed to execute \"" + currentCommand_->message_ + "\".";
      LogWidget::AddEntry(logMessage.c_str());
    }

    currentCommand_ = nullptr;

    SetSceneAndProjectDirty();
  }

  void CommandQueue::Undo(bool log)
  {
    if (currentCommand_)
    {
      return;
    }

    UndoInternal(log);

    while (!undoStack_.empty() && undoStack_.top()->chains_)
    {
      UndoInternal(false);
    }

    SetSceneAndProjectDirty();
  }

  void CommandQueue::UndoInternal(bool log)
  {
    if (undoStack_.empty())
    {
      if (log)
      {
        LogWidget::AddEntry("Nothing to undo.");
      }

      return;
    }

    std::shared_ptr<Command> undoCommand = undoStack_.top();
    undoCommand->Undo();

    undoStack_.pop();
    redoStack_.push(undoCommand);

    if (log)
    {
      std::string logMessage = "Undo: " + undoCommand->GetMessage();
      LogWidget::AddEntry(logMessage.c_str());
    }
  }

  void CommandQueue::Redo(bool log)
  {
    if (currentCommand_)
    {
      return;
    }

    while (RedoInternal(log)) {};

    SetSceneAndProjectDirty();
  }

  bool CommandQueue::RedoInternal(bool log)
  {
    if (redoStack_.empty())
    {
      if (log)
      {
        LogWidget::AddEntry("Nothing to redo.");
      }

      return false;
    }
    
    std::shared_ptr<Command> redoCommand = redoStack_.top();
    redoCommand->Redo();

    redoStack_.pop();
    undoStack_.push(redoCommand);

    if (redoCommand->chains_)
    {
      return true;
    }
    else
    {
      if (log)
      {
        std::string logMessage = "Redo: " + redoCommand->GetMessage();
        LogWidget::AddEntry(logMessage.c_str());
      }

      return false;
    }
  }

  bool CommandQueue::UndoAvailable()
  {
    return !undoStack_.empty();
  }

  bool CommandQueue::RedoAvailable()
  {
    return !redoStack_.empty();
  }

  void CommandQueue::SetSceneAndProjectDirty()
  {
    Editor::Get().Data().sceneIsDirty_ = true;
    //Editor::Get().Data().projectIsDirty_ = true;
  }

  void CommandQueue::Clear()
  {
    currentCommand_ = nullptr;
    ClearUndoStack();
    ClearRedoStack();
  }

  void CommandQueue::ClearUndoStack()
  {
    undoStack_ = std::stack<std::shared_ptr<Command>>();
  }

  void CommandQueue::ClearRedoStack()
  {
    redoStack_ = std::stack<std::shared_ptr<Command>>();
  }
}