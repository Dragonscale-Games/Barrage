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
#include "Widgets/Component/ComponentArray/ComponentArrayWidget.hpp"
#include "Widgets/Component/SharedComponent/SharedComponentWidget.hpp"
#include "Editor/Editor.hpp"
#include <string>
#include "Widgets/Data/DataWidget.hpp"

namespace Barrage
{
  void InspectorWidget::Use()
  {
    ImGui::Begin("Inspector");

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

    if (ImGui::CollapsingHeader("Tags"))
    {
      const std::vector<std::string_view> tags = poolArchetype->GetTags();
      for (const std::string_view& tag : tags)
      {
        ImGui::Text(tag.data());
      }
    }

    const SharedComponentMap& sharedComponents = poolArchetype->GetSharedComponents();
    for (auto& sharedComponent : sharedComponents)
    {
      SharedComponentWidget::Use(sharedComponent.first, sharedComponent.second);
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
}