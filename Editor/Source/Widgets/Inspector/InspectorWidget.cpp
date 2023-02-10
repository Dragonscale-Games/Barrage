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

namespace Barrage
{
  InspectorWidget::InspectorWidget(EditorData& editorData, Engine& engine) :
    Widget(editorData, engine)
  {
  }

  void InspectorWidget::UseWidget()
  {
    ImGui::Begin("Inspector");

    ObjectManager& objectManager = engine_.Spaces().GetSpace(editorData_.selectedSpace_.data())->GetObjectManager();

    if (!editorData_.selectedPool_.empty())
    {
      PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(editorData_.selectedPool_);

      if (poolArchetype)
      {
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Text("Pool:");
        ImGui::SameLine();
        ImGui::Text(editorData_.selectedPool_.data());
        ImGui::Spacing();
        ImGui::Separator();
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
           ComponentWidget::UseWidget(component.first, component.second);
        }

        ImGui::Text(" ");
      }
    }

    if (!editorData_.selectedObject_.empty())
    {
      ImGui::Separator();
      ImGui::Spacing();
      ImGui::Text("Object:");
      ImGui::SameLine();
      ImGui::Text(editorData_.selectedObject_.data());
      ImGui::Spacing();
      ImGui::Separator();
      ImGui::Spacing();

      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(editorData_.selectedObject_);

      if (objectArchetype)
      {
        for (auto& component : objectArchetype->components_)
        {
          ComponentWidget::UseWidget(component.first, component.second);
        }
      }
    }

    ImGui::End();
  }
}