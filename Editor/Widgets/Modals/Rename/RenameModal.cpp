/* ======================================================================== */
/*!
 * \file            RenameModal.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A selection window that pops up when the user tries to rename something.
 */
 /* ======================================================================== */

#include "RenameModal.hpp"
#include <Editor.hpp>
#include "imgui/imgui_stdlib.h"

namespace Barrage
{
  std::string RenameModal::newName_ = std::string();
  
  void RenameModal::Use(const char* strId, RenameCallback callback)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
    {
      return;
    }

    ImGui::Text("Enter new name:");
    ImGui::Spacing();
    ImGui::InputText("###RenameTextBox", &newName_);
    ImGui::Spacing();

    bool nameIsEmpty = newName_.empty();

    if (nameIsEmpty)
    {
      ImGui::BeginDisabled();
    }

    if (ImGui::Button("Ok", ImVec2(120.0f, 0.0f)))
    {
      if (callback)
      {
        callback(newName_);
        newName_.clear();
        ImGui::CloseCurrentPopup();
      }
    }

    if (nameIsEmpty)
    {
      ImGui::EndDisabled();
    }

    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
    {
      newName_.clear();
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
   
    ImGui::EndPopup();
  }
}