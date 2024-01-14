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
#include "Editor.hpp"

#include "Widgets/Components/ComponentArrayWidget.hpp"
#include "Widgets/Components/ComponentWidget.hpp"

namespace Barrage
{
  void InspectorWidget::Use()
  {
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove);

    if (Editor::Get().Data().selectedScene_.empty() || Editor::Get().Data().selectedPool_.empty())
    {
      ImGui::End();
      return;
    }

    Scene* scene = Engine::Get().Scenes().GetScene(Editor::Get().Data().selectedScene_);

    if (scene == nullptr || scene->poolArchetypes_.count(Editor::Get().Data().selectedPool_) == 0)
    {
      ImGui::End();
      return;
    }

    PoolArchetype& poolArchetype = scene->poolArchetypes_.at(Editor::Get().Data().selectedPool_);

    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Pool:");
    ImGui::SameLine();
    ImGui::Text(Editor::Get().Data().selectedPool_.c_str());
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushID(Editor::Get().Data().selectedPool_.c_str());

    /*unsigned old_capacity_value = poolArchetype->GetCapacity();
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
    }*/

    if (ImGui::CollapsingHeader("Tags"))
    {
      StringSet& tags = poolArchetype.tags_;
      for (const std::string& tag : tags)
      {
        ImGui::PushID(tag.data());
        if (ImGui::Button("X"))
        {
          /*EditorData& editorData = Editor::Instance->Data();
          DeleteTag* command = new DeleteTag(
            editorData.selectedScene_,
            editorData.selectedPool_,
            tag);
          Editor::Instance->Command().Send(command);*/
        }
        ImGui::SameLine();
        ImGui::Text(tag.data());
        ImGui::PopID();
      }

      if (ImGui::Button("Add tag"))
      {
        //Editor::Instance->Data().openTagModal_ = true;
      }
    }

    ComponentMap& components = poolArchetype.components_;
    for (auto& component : components)
    {
      ComponentWidget::Use(component.first, component.second);
    }

    ImGui::Text(" ");

    ImGui::PopID();

    bool objectSelected = !Editor::Get().Data().selectedStartingObject_.empty() || !Editor::Get().Data().selectedSpawnArchetype_.empty();
    
    if (objectSelected)
    {
      bool isSpawnArchetype = !Editor::Get().Data().selectedSpawnArchetype_.empty();
      ObjectArchetype& objectArchetype = isSpawnArchetype ? 
        poolArchetype.spawnArchetypes_.at(Editor::Get().Data().selectedSpawnArchetype_) : 
        poolArchetype.startingObjects_.at(Editor::Get().Data().selectedStartingObject_);


      ImGui::Separator();
      ImGui::Spacing();
      ImGui::Text("Object:");
      ImGui::SameLine();
      ImGui::Text(objectArchetype.name_.c_str());
      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      ImGui::PushID(objectArchetype.name_.c_str());

      ComponentArrayMap& componentArrays = objectArchetype.componentArrays_;
      for (auto& componentArray : componentArrays)
      {
        ComponentArrayWidget::Use(componentArray.first, componentArray.second);
      }

      ImGui::PopID();
    }

    ImGui::End();
  }
}