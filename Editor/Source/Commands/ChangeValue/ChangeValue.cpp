/* ======================================================================== */
/*!
 * \file            ChangeValue.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Generic command for changing a value.
 */
 /* ======================================================================== */

#include "ChangeValue.hpp"
#include <Editor/Editor.hpp>

namespace Barrage
{
  ChangeValue::Writer::Writer(DataWrapper value) :
    value_(value)
  {
  }

  ChangeValue::ChangeValue(const std::string& valueName, rttr::variant valuePointer) :
    Command("Value changed. (" + valueName + ")"),
    valuePointer_(valuePointer),
    value_(valuePointer_),
    valueName_(valueName),
    writer_(nullptr)
  {
  }

  ChangeValue::~ChangeValue()
  {
    delete writer_;
  }

  const std::string& ChangeValue::GetValueName()
  {
    return valueName_;
  }

  void ChangeValue::SetChainUndo(bool enable)
  {
    chains_ = enable;
  }

  bool ChangeValue::ValueWasSet()
  {
    return (writer_ != nullptr);
  }

  bool ChangeValue::Execute()
  {
    if (writer_)
    {
      writer_->WriteNewValue();
      Editor::Instance->Data().sceneIsDirty_ = true;
      return true;
    }

    return false;
  }

  void ChangeValue::Undo()
  {
    if (writer_)
    {
      writer_->WriteOldValue();
      Editor::Instance->Data().sceneIsDirty_ = true;
    }
  }

  void ChangeValue::Redo()
  {
    Execute();
  }
}