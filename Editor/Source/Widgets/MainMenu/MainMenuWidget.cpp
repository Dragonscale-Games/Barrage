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
      if (ImGui::MenuItem("Exit"))
      {
        Editor::Instance->Data().isRunning_ = false;
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit"))
    {
      if (ImGui::MenuItem("Undo"))
      {
        Editor::Instance->Command().Undo();
      }

      if (ImGui::MenuItem("Redo"))
      {
        Editor::Instance->Command().Redo();
      }

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Create"))
    {
      if (ImGui::MenuItem("Pool"))
      {
        std::string& space = Editor::Instance->Data().selectedSpace_;
        std::string& scene = Editor::Instance->Data().selectedScene_;
        Editor::Instance->Command().Send(new CreatePool(space, scene));
      }

      if (Editor::Instance->Data().selectedPool_.empty())
      {
        ImGui::BeginDisabled();
      }

      if (ImGui::MenuItem("Object"))
      {
        std::string& space = Editor::Instance->Data().selectedSpace_;
        std::string& scene = Editor::Instance->Data().selectedScene_;
        std::string& pool = Editor::Instance->Data().selectedPool_;
        Editor::Instance->Command().Send(new CreateObject(space, scene, pool));
      }

      if (Editor::Instance->Data().selectedPool_.empty())
      {
        ImGui::EndDisabled();
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}