/* ======================================================================== */
/*!
 * \file            MainMenuWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main menu bar that shows at the top of the screen.
 */
 /* ======================================================================== */

#include "MainMenuWidget.hpp"
#include <Editor/Editor.hpp>
#include "Commands/Create/Pool/CreatePool.hpp"
#include "Commands/Create/Object/CreateObject.hpp"

namespace Barrage
{
  void MainMenuWidget::Use()
  {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("Save scene"))
      {
        SaveScene();
      }
      
      if (ImGui::MenuItem("Load scene"))
      {
        LoadScene();
      }

      ImGui::Separator();

      if (ImGui::MenuItem("Exit"))
      {
        Editor::Instance->Data().isRunning_ = false;
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit"))
    {
      bool undoAvailable = Editor::Instance->Command().UndoAvailable();
      
      if (!undoAvailable)
      {
        ImGui::BeginDisabled();
      }

      if (ImGui::MenuItem("Undo"))
      {
        Editor::Instance->Command().Undo();
      }

      if (!undoAvailable)
      {
        ImGui::EndDisabled();
      }

      bool redoAvailable = Editor::Instance->Command().RedoAvailable();

      if (!redoAvailable)
      {
        ImGui::BeginDisabled();
      }

      if (ImGui::MenuItem("Redo"))
      {
        Editor::Instance->Command().Redo();
      }

      if (!redoAvailable)
      {
        ImGui::EndDisabled();
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Create"))
    {
      if (ImGui::MenuItem("Pool"))
      {
        std::string& scene = Editor::Instance->Data().selectedScene_;
        Editor::Instance->Command().Send(new CreatePool(scene));
      }

      if (Editor::Instance->Data().selectedPool_.empty())
      {
        ImGui::BeginDisabled();
      }

      if (ImGui::MenuItem("Object"))
      {
        std::string& scene = Editor::Instance->Data().selectedScene_;
        std::string& pool = Editor::Instance->Data().selectedPool_;
        Editor::Instance->Command().Send(new CreateObject(scene, pool));
      }

      if (Editor::Instance->Data().selectedPool_.empty())
      {
        ImGui::EndDisabled();
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  void MainMenuWidget::SaveScene()
  {
    EditorData& editorData = Editor::Instance->Data();

    if (editorData.selectedScene_.empty())
    {
      return;
    }

    Scene* scene = Engine::Instance->Scenes().GetScene(editorData.selectedScene_);

    if (scene == nullptr)
    {
      return;
    }

    std::string path = editorData.selectedScene_ + ".scene";
    if (Scene::SaveToFile(scene, path))
    {
      LogWidget::AddEntry("Saved scene \"" + editorData.selectedScene_ + "\" to \"" + path + "\".");
    }
    else
    {
      LogWidget::AddEntry("Could not save scene \"" + editorData.selectedScene_ + "\".");
    }
  }

  void MainMenuWidget::LoadScene()
  {
    EditorData& editorData = Editor::Instance->Data();

    if (editorData.selectedScene_.empty())
    {
      return;
    }

    std::string path = editorData.selectedScene_ + ".scene";

    Scene* scene = Scene::LoadFromFile(path);
    
    if (scene == nullptr)
    {
      return;
    }
    
    editorData.nextScene_ = scene;
  }
}