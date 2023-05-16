/* ======================================================================== */
/*!
 * \file            SharedComponentModal.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A selection window that pops up when the user tries to add a shared
   component to a pool.
 */
 /* ======================================================================== */

#include "SharedComponentModal.hpp"
#include <Objects/Components/ComponentAllocator.hpp>
#include <Editor/Editor.hpp>
#include <Commands/Create/SharedComponent/CreateSharedComponent.hpp>

namespace Barrage
{
  void SharedComponentModal::Use(const char* strId)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
    {
      return;
    }

    auto& sharedComponentNames = ComponentAllocator::GetSharedComponentNames();
    EditorData& editorData = Editor::Instance->Data();

    if (sharedComponentNames.size())
    {
      ImGui::Text("Select a shared component to add:");
      ImGui::Spacing();

      std::string_view previewString;

      if (Editor::Instance->Data().selectedSharedComponent_.empty())
      {
        previewString = " ";
      }
      else
      {
        previewString = editorData.selectedSharedComponent_;
      }

      ImGui::PushItemWidth(240.0f);
      if (ImGui::BeginCombo("##SharedComponentModalSelector", previewString.data()))
      {
        for (auto& sharedComponentName : sharedComponentNames)
        {
          if (ImGui::Selectable(sharedComponentName.data(), sharedComponentName == editorData.selectedSharedComponent_))
          {
            editorData.selectedSharedComponent_ = sharedComponentName;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::Spacing();
      ImGui::Spacing();

      if (ImGui::Button("Add", ImVec2(120.0f, 0.0f))) 
      { 
        Editor::Instance->Command().Send(new CreateSharedComponent(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedSharedComponent_));
        ImGui::CloseCurrentPopup(); 
      }
      ImGui::SameLine();
      if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f))) 
      { 
        ImGui::CloseCurrentPopup(); 
      }
      ImGui::SetItemDefaultFocus();
    }
    else
    {
      ImGui::Text("No shared components registered.");

      if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::EndPopup();
  }
}