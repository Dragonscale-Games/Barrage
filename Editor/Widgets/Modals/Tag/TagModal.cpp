/* ======================================================================== */
/*!
 * \file            TagModal.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A selection window that pops up when the user tries to add a tag to a 
   pool.
 */
 /* ======================================================================== */

#include "TagModal.hpp"
#include <Objects/Components/ComponentAllocator.hpp>
#include <Editor.hpp>
#include <Commands/Create/Tag/CreateTag.hpp>

namespace Barrage
{
  void TagModal::Use(const char* strId)
  {
    if (!ImGui::BeginPopupModal(strId, NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
    {
      return;
    }

    auto& tags = ComponentAllocator::GetTagNames();
    EditorData& editorData = Editor::Instance->Data();

    if (tags.size())
    {
      ImGui::Text("Select a tag to add:");
      ImGui::Spacing();

      std::string_view previewString;

      if (Editor::Instance->Data().selectedTag_.empty())
      {
        previewString = " ";
      }
      else
      {
        previewString = editorData.selectedTag_;
      }

      ImGui::PushItemWidth(240.0f);
      if (ImGui::BeginCombo("##TagModalSelector", previewString.data()))
      {
        for (auto& tag : tags)
        {
          if (ImGui::Selectable(tag.data(), tag == editorData.selectedTag_))
          {
            editorData.selectedTag_ = tag;
          }
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::Spacing();
      ImGui::Spacing();

      if (ImGui::Button("Add", ImVec2(120.0f, 0.0f)))
      {
        Editor::Instance->Command().Send(new CreateTag(editorData.selectedScene_, editorData.selectedPool_, editorData.selectedTag_));
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
      ImGui::Text("No tags registered.");

      if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
      {
        ImGui::CloseCurrentPopup();
      }
    }

    ImGui::EndPopup();
  }
}