/* ======================================================================== */
/*!
 * \file            ComponentArrayModal.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A selection window that pops up when the user tries to add a component
   array to a pool.
 */
 /* ======================================================================== */

#include "ComponentArrayModal.hpp"
#include <Objects/Components/ComponentFactory.hpp>
#include <Editor.hpp>
#include <Commands/Create/ComponentArray/CreateComponentArray.hpp>

namespace Barrage
{
  void ComponentArrayModal::Use(const char* strId)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
    {
      return;
    }

    auto& componentArrayNames = ComponentFactory::GetComponentArrayNames();
    EditorData& editorData = Editor::Get().Data();

    if (componentArrayNames.size())
    {
      ImGui::Text("Select a component array to add:");
      ImGui::Spacing();

      std::string previewString;

      if (Editor::Get().Data().selectedComponentArray_.empty())
      {
        previewString = " ";
      }
      else
      {
        previewString = editorData.selectedComponentArray_;
      }

      ImGui::PushItemWidth(240.0f);
      if (ImGui::BeginCombo("##ComponentArrayModalSelector", previewString.c_str()))
      {
        for (auto& componentArrayName : componentArrayNames)
        {
          if (ImGui::Selectable(componentArrayName.c_str(), componentArrayName == editorData.selectedComponentArray_))
          {
            editorData.selectedComponentArray_ = componentArrayName;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::Spacing();
      ImGui::Spacing();

      if (ImGui::Button("Add", ImVec2(120.0f, 0.0f)))
      {
        Editor::Get().Command().Send(std::make_shared<CreateComponentArray>(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedComponentArray_));
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
      ImGui::Text("No component arrays registered.");

      if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::EndPopup();
  }
}