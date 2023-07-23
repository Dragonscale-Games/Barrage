/* ======================================================================== */
/*!
 * \file            InspectorWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit components for pools and game objects.
 */
 /* ======================================================================== */

#include "InspectorWidget.hpp"
#include "Widgets/Components/ComponentArray/ComponentArrayWidget.hpp"
#include "Widgets/Components/Component/ComponentWidget.hpp"
#include "Editor.hpp"
#include <string>
#include "Widgets/Data/DataWidget.hpp"
#include "Commands/Delete/Tag/DeleteTag.hpp"
#include "Commands/Edit/Capacity/EditCapacity.hpp"
#include "Widgets/Windows/Log/LogWidget.hpp"

namespace Barrage
{
  ImVec2 InspectorWidget::size_ = ImVec2(0.0f, 0.0f);
  
  void InspectorWidget::Use()
  {
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove);

    size_ = ImGui::GetWindowSize();

    if (Editor::Instance->Data().selectedScene_.empty() || Editor::Instance->Data().selectedPool_.empty())
    {
      ImGui::End();
      return;
    }

    Scene* scene = Engine::Instance->Scenes().GetScene(Editor::Instance->Data().selectedScene_);
    PoolArchetype* poolArchetype = scene->GetPoolArchetype(Editor::Instance->Data().selectedPool_);

    if (poolArchetype == nullptr)
    {
      ImGui::End();
      return;
    }

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Pool:");
    ImGui::SameLine();
    ImGui::Text(Editor::Instance->Data().selectedPool_.c_str());
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushID(Editor::Instance->Data().selectedPool_.c_str());

    //DataWidget::Use(poolArchetype->capacity_, "capacity");

    //ImGui::Spacing();

    unsigned old_capacity_value = poolArchetype->GetCapacity();
    rttr::variant capacity_value = old_capacity_value;
    DataWidget::DataObject capacity_object("Capacity", capacity_value);

    ImGui::Spacing();
    DataWidget::Use(capacity_object);
    ImGui::Spacing();

    if (capacity_object.ValueWasSet())
    {
      unsigned new_value = capacity_object.GetValue<unsigned>();

      if (new_value < 1)
      {
        new_value = 1;
        LogWidget::AddEntry("Capacity cannot go lower than 1.");
      }
      else if (new_value < poolArchetype->GetStartingObjects().size())
      {
        new_value = static_cast<unsigned>(poolArchetype->GetStartingObjects().size());
        LogWidget::AddEntry("Capacity cannot go lower than number of objects in pool.");
      }
      
      EditorData& editorData = Editor::Instance->Data();
      EditCapacity* capacity_command = new EditCapacity(
        editorData.selectedScene_,
        editorData.selectedPool_,
        new_value,
        capacity_object.ChainUndoEnabled());
      Editor::Instance->Command().Send(capacity_command);
    }

    if (ImGui::CollapsingHeader("Tags"))
    {
      const std::vector<std::string_view> tags = poolArchetype->GetTags();
      for (const std::string_view& tag : tags)
      {
        ImGui::PushID(tag.data());
        if (ImGui::Button("X"))
        {
          EditorData& editorData = Editor::Instance->Data();
          DeleteTag* command = new DeleteTag(
            editorData.selectedScene_,
            editorData.selectedPool_,
            tag);
          Editor::Instance->Command().Send(command);
        }
        ImGui::SameLine();
        ImGui::Text(tag.data());
        ImGui::PopID();
      }

      if (ImGui::Button("Add tag"))
      {
        Editor::Instance->Data().openTagModal_ = true;
      }
    }

    const ComponentMap& sharedComponents = poolArchetype->GetComponents();
    for (auto& sharedComponent : sharedComponents)
    {
      ComponentWidget::Use(sharedComponent.first, sharedComponent.second);
    }

    ImGui::Text(" ");

    ImGui::PopID();

    if (!Editor::Instance->Data().selectedObject_.empty())
    {
      ObjectArchetype* objectArchetype = poolArchetype->GetObjectArchetype(Editor::Instance->Data().selectedObject_);

      if (objectArchetype)
      {
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Text("Object:");
        ImGui::SameLine();
        ImGui::Text(Editor::Instance->Data().selectedObject_.c_str());
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::PushID(Editor::Instance->Data().selectedObject_.c_str());
        
        const ComponentArrayMap& componentArrays = objectArchetype->GetComponentArrays();
        for (auto& componentArray : componentArrays)
        {
          ComponentArrayWidget::Use(componentArray.first, componentArray.second);
        }

        ImGui::PopID();
      }
    }

    ImGui::End();
  }

  ImVec2 InspectorWidget::GetSize()
  {
    return size_;
  }
}