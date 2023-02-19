/* ======================================================================== */
/*!
 * \file            ComponentWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit the values of a component.
 */
 /* ======================================================================== */

#include "ComponentWidget.hpp"
#include "Objects/Components/BaseClasses/BaseComponent.hpp"
#include "Widgets/Data/DataWidget.hpp"
#include <iostream>
#include "Widgets/Popups/ComponentArray/ComponentArrayPopupWidget.hpp"
#include "Widgets/Popups/SharedComponent/SharedComponentPopupWidget.hpp"
namespace Barrage
{
  void ComponentWidget::Use(const std::string_view& componentName, Component* component)
  {
    if (component == nullptr)
    {
      return;
    }

    ImGui::PushID(componentName.data());

    if (component->GetType() == Component::Type::ARRAY)
    {
      EditComponentArray(componentName, dynamic_cast<ComponentArray*>(component));
    }
    else if (component->GetType() == Component::Type::SHARED)
    {
      EditSharedComponent(componentName, dynamic_cast<SharedComponent*>(component));
    }

    ComponentArrayPopupWidget::Use("Component Array Popup", componentName);
    SharedComponentPopupWidget::Use("Shared Component Popup", componentName);

    ImGui::PopID();
  }

  void ComponentWidget::EditComponentArray(const std::string_view& componentName, ComponentArray* componentArray)
  {
    bool headerOpen = ImGui::CollapsingHeader(componentName.data());
    
    std::string derivedArrayName = componentName.data();
    derivedArrayName += "*";
    rttr::variant arrayPointer = componentArray;
    const rttr::type arrayType = rttr::type::get_by_name(derivedArrayName.c_str());

    bool success = arrayPointer.convert(arrayType);

    if (!success)
    {
      return;
    }

    for (auto& prop : arrayType.get_properties())
    {
      std::string propName = prop.get_name().data();
      
      if (derivedArrayName.find(propName) == std::string::npos)
      {
        continue;
      }

      const rttr::type dataType = rttr::type::get_by_name(propName);
      rttr::variant dataPointer = prop.get_value(arrayPointer);

      if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
      {
        ImGui::OpenPopup("Component Array Popup");
      }

      if (dataType.is_valid() && headerOpen)
      {
        ImGui::Spacing();
        DataWidget::Use(dataPointer);
        ImGui::Spacing();
      }
    }
  }

  void ComponentWidget::EditSharedComponent(const std::string_view& componentName, SharedComponent* component)
  {
    bool headerOpen = ImGui::CollapsingHeader(componentName.data());
    
    std::string derivedComponentName = componentName.data();
    derivedComponentName += "*";
    rttr::variant componentPointer = component;
    const rttr::type componentType = rttr::type::get_by_name(derivedComponentName.c_str());

    bool success = componentPointer.convert(componentType);

    if (!success)
    {
      return;
    }

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      ImGui::OpenPopup("Shared Component Popup");
    }

    if (headerOpen)
    {
      ImGui::Spacing();
      DataWidget::Use(componentPointer);
      ImGui::Spacing();
    }
  }
}