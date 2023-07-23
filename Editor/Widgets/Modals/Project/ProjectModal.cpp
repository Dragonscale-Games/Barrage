/* ======================================================================== */
/*!
 * \file            ProjectModal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The window that lets the user either create a new project or open an
   existing one.
 */
 /* ======================================================================== */

#include "ProjectModal.hpp"
#include <Editor.hpp>

namespace Barrage
{
  void ProjectModal::Use(const char* strId)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
      return;
    }

    if (ImGui::Button("New project", ImVec2(120.0f, 0.0f)))
    {
      if (CreateNewProject())
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::SetItemDefaultFocus();

    if (ImGui::Button("Open project", ImVec2(120.0f, 0.0f)))
    {
      if (OpenProject())
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::EndPopup();
  }

  bool ProjectModal::CreateNewProject()
  {
    return Editor::Instance->CreateProject("BulletGame");
  }

  bool ProjectModal::OpenProject()
  {
    return Editor::Instance->OpenProject();
  }
}