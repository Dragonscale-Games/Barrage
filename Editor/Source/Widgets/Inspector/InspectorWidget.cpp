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

    if (!editorData_.selectedPoolArchetype_.empty())
    {
      PoolArchetype* poolArchetype = objectManager.GetPoolArchetype(editorData_.selectedPoolArchetype_);

      ImGui::Text("+-------------------+");
      ImGui::Text("|       Tags        |");
      ImGui::Text("+-------------------+");

      for (std::string_view& tag : poolArchetype->tags_)
      {
        ImGui::Text(tag.data());
      }

      ImGui::Text(" ");
      ImGui::Text("+-------------------+");
      ImGui::Text("|  Pool Components  |");
      ImGui::Text("+-------------------+");

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
      ImGui::Text("+-------------------+");
      ImGui::Text("| Object Components |");
      ImGui::Text("+-------------------+");

      for (std::string_view& componentName : poolArchetype->componentArrayNames_)
      {
        if (ImGui::CollapsingHeader(componentName.data()))
        {
          rttr::type componentType = rttr::type::get_by_name(componentName.data());
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

    if (!editorData_.selectedObject_.empty())
    {
      
    }

    ImGui::End();
  }
}