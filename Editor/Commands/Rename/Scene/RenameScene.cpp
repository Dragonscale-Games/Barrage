/* ======================================================================== */
/*!
 * \file            RenameScene.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a scene.
 */
 /* ======================================================================== */

#include "RenameScene.hpp"
#include <Editor.hpp>

namespace Barrage
{
  RenameScene::RenameScene(
    const std::string& sceneName,
    const std::string& newName) :
    Command("Renamed scene \"" + sceneName + "\" to \"" + newName + "\"."),
    sceneName_(sceneName),
    newName_(newName)
  {
  }

  bool RenameScene::Execute()
  {
    bool success = Engine::Instance->Scenes().RenameScene(sceneName_, newName_);
    
    if (success)
    {
      EditorData& editorData = Editor::Instance->Data();
      if (editorData.selectedScene_ == sceneName_)
      {
        editorData.selectedScene_ = newName_;
      }
    }

    return success;
  }

  void RenameScene::Undo()
  {
    Engine::Instance->Scenes().RenameScene(newName_, sceneName_);

    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedScene_ == newName_)
    {
      editorData.selectedScene_ = sceneName_;
    }
  }

  void RenameScene::Redo()
  {
    Engine::Instance->Scenes().RenameScene(sceneName_, newName_);

    EditorData& editorData = Editor::Instance->Data();
    if (editorData.selectedScene_ == sceneName_)
    {
      editorData.selectedScene_ = newName_;
    }
  }
}