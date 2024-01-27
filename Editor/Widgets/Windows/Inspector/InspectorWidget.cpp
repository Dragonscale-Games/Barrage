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
#include "Widgets/Popups/ComponentArray/ComponentArrayPopupWidget.hpp"

#include "Widgets/Data/DataWidget.hpp"

#include "Commands/Delete/Tag/DeleteTag.hpp"
#include "Commands/Edit/Capacity/EditCapacity.hpp"

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

    unsigned old_capacity_value = poolArchetype.capacity_;
    rttr::variant capacity_value = old_capacity_value;
    DataWidget::DataObject capacity_object("Capacity", capacity_value);

    ImGui::Spacing();
    DataWidget::Use(capacity_object);
    ImGui::Spacing();

    if (capacity_object.ValueWasSet())
    {
      unsigned new_value = capacity_object.GetValue<unsigned>();

      EditorData& editorData = Editor::Get().Data();
      Editor::Get().Command().Send(std::make_shared<EditCapacity>(
        editorData.selectedScene_,
        editorData.selectedPool_,
        new_value,
        capacity_object.ChainUndoEnabled()
      ));
    }

    if (ImGui::CollapsingHeader("Tags"))
    {
      StringSet& tags = poolArchetype.tags_;
      for (const std::string& tag : tags)
      {
        ImGui::PushID(tag.data());
        if (ImGui::Button("X"))
        {
          EditorData& editorData = Editor::Get().Data();
          Editor::Get().Command().Send(std::make_shared<DeleteTag>(
            editorData.selectedScene_,
            editorData.selectedPool_,
            tag));
        }
        ImGui::SameLine();
        ImGui::Text(tag.data());
        ImGui::PopID();
      }

      if (ImGui::Button("Add tag"))
      {
        Editor::Get().Data().openTagModal_ = true;
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
    else
    {
      ImGui::Separator();
      ImGui::Spacing();
      ImGui::Text("Object: (none selected)");
      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();
      
      for (auto& componentArrayName : poolArchetype.componentArrayNames_)
      {
        ImGui::PushID(componentArrayName.c_str());

        bool headerOpen = ImGui::CollapsingHeader(componentArrayName.c_str());

        if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
        {
          ImGui::OpenPopup("Component Array Popup");
        }

        if (headerOpen)
        {
          ImGui::Text("(no object selected)");
        }

        ComponentArrayPopupWidget::Use("Component Array Popup", componentArrayName);

        ImGui::PopID();
      }
    }

    ImGui::End();
  }
}