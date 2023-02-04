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

namespace Barrage
{
  InspectorWidget::InspectorWidget(EditorData& editorData, Engine& engine) :
    Widget(editorData, engine)
  {
  }

  void InspectorWidget::UseWidget()
  {
    ImGui::Begin("Inspector");

    ObjectManager& objectManager = engine_.Spaces().GetSpace("Demo Space")->GetObjectManager();

    if (!editorData_.selectedPool_.empty())
    {
      PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(editorData_.selectedPool_);

      if (poolArchetype)
      {
        ImGui::Text("Pool:");
        ImGui::SameLine();
        ImGui::Text(editorData_.selectedPool_.data());

        if (ImGui::CollapsingHeader("Tags"))
        {
          for (std::string_view& tag : poolArchetype->tags_)
          {
            ImGui::Text(tag.data());
          }
        }

        for (auto& component : poolArchetype->sharedComponents_)
        {
          if (ImGui::CollapsingHeader(component.first.data()))
          {
            rttr::type componentType = rttr::type::get_by_name(component.first.data());
            if (componentType.is_valid())
            {
              for (auto& prop : componentType.get_properties())
              {
                ImGui::Text(prop.get_name().data());
              }
            }
          }
        }

        ImGui::Text(" ");
      }
    }

    if (!editorData_.selectedObject_.empty())
    {
      ImGui::Text("Object:");
      ImGui::SameLine();
      ImGui::Text(editorData_.selectedObject_.data());

      ObjectArchetype* objectArchetype = objectManager.GetObjectArchetype(editorData_.selectedObject_);

      if (objectArchetype)
      {
        for (auto& componentName : objectArchetype->components_)
        {
          if (ImGui::CollapsingHeader(componentName.first.data()))
          {
            rttr::type componentType = rttr::type::get_by_name(componentName.first.data());
            if (componentType.is_valid())
            {
              for (auto& prop : componentType.get_properties())
              {
                ImGui::Text(prop.get_name().data());
              }
            }
          }
        }
      }
    }

    ImGui::End();
  }
}