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
#include "Widgets/Component/ComponentWidget.hpp"
#include "Editor/Editor.hpp"
#include <string>
#include "Widgets/Data/DataWidget.hpp"

namespace Barrage
{
  void InspectorWidget::Use()
  {
    ImGui::Begin("Inspector");

    ObjectManager& objectManager = Engine::Instance->Spaces().GetSpace(Editor::Instance->Data().selectedSpace_)->GetObjectManager();

    if (!Editor::Instance->Data().selectedPool_.empty())
    {
      PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(Editor::Instance->Data().selectedPool_);

      if (poolArchetype)
      {
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Text("Pool:");
        ImGui::SameLine();
        ImGui::Text(Editor::Instance->Data().selectedPool_.c_str());
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::PushID(Editor::Instance->Data().selectedPool_.c_str());

        DataWidget::Use(poolArchetype->capacity_, "capacity");

        ImGui::Spacing();

        if (ImGui::CollapsingHeader("Tags"))
        {
          for (std::string_view& tag : poolArchetype->tags_)
          {
            ImGui::Text(tag.data());
          }
        }

        for (auto& component : poolArchetype->sharedComponents_)
        {
           ComponentWidget::Use(component.first, component.second);
        }

        ImGui::Text(" ");

        ImGui::PopID();
      }
    }

    if (!Editor::Instance->Data().selectedObject_.empty())
    {
      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(Editor::Instance->Data().selectedObject_);

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
        
        for (auto& component : objectArchetype->components_)
        {
          ComponentWidget::Use(component.first, component.second);
        }

        ImGui::PopID();
      }

      
    }

    ImGui::End();
  }
}