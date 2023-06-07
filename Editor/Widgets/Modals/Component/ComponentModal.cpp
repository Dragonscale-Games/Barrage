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

#include "ComponentModal.hpp"
#include <Objects/Components/ComponentAllocator.hpp>
#include <Editor.hpp>
#include <Commands/Create/Component/CreateComponent.hpp>

namespace Barrage
{
  void ComponentModal::Use(const char* strId)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
    {
      return;
    }

    auto& componentNames = ComponentAllocator::GetComponentNames();
    EditorData& editorData = Editor::Instance->Data();

    if (componentNames.size())
    {
      ImGui::Text("Select a component to add:");
      ImGui::Spacing();

      std::string_view previewString;

      if (Editor::Instance->Data().selectedComponent_.empty())
      {
        previewString = " ";
      }
      else
      {
        previewString = editorData.selectedComponent_;
      }

      ImGui::PushItemWidth(240.0f);
      if (ImGui::BeginCombo("##ComponentModalSelector", previewString.data()))
      {
        for (auto& componentName : componentNames)
        {
          if (ImGui::Selectable(componentName.data(), componentName == editorData.selectedComponent_))
          {
            editorData.selectedComponent_ = componentName;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::Spacing();
      ImGui::Spacing();

      if (ImGui::Button("Add", ImVec2(120.0f, 0.0f))) 
      { 
        Editor::Instance->Command().Send(new CreateComponent(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedComponent_));
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
      ImGui::Text("No components registered.");

      if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::EndPopup();
  }
}