/* ======================================================================== */
/*!
 * \file            SaveProjectModal.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The "Save project before closing?" popup window.
 */
 /* ======================================================================== */

#include "SaveProjectModal.hpp"
#include <Editor.hpp>

namespace Barrage
{
  void SaveProjectModal::Use(const char* strId)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
      return;
    }

    EditorData& editorData = Editor::Get().Data();

    ImGui::Text("Save project before closing?");
    ImGui::Spacing();

    if (ImGui::Button("Save", ImVec2(120.0f, 0.0f)))
    {
      if (Editor::Get().SaveProject(Editor::Get().Data().projectDirectory_))
      {
        editorData.isRunning_ = false;
      }
    }
    ImGui::SameLine();
    if (ImGui::Button("Don't save", ImVec2(120.0f, 0.0f)))
    {
      editorData.projectIsDirty_ = false;
      editorData.isRunning_ = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
    {
      ImGui::CloseCurrentPopup();
    }

    ImGui::SetItemDefaultFocus();

    ImGui::EndPopup();
  }
}