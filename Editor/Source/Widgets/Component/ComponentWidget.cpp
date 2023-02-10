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

namespace Barrage
{
  void ComponentWidget::UseWidget(const std::string_view& componentName, Component* component)
  {
    if (component == nullptr)
    {
      return;
    }

    if (component->GetType() == Component::Type::ARRAY)
    {
      EditComponentArray(componentName, dynamic_cast<ComponentArray*>(component));
    }
    else if (component->GetType() == Component::Type::SHARED)
    {
      EditSharedComponent(componentName, dynamic_cast<SharedComponent*>(component));
    }
  }

  void ComponentWidget::EditComponentArray(const std::string_view& componentName, ComponentArray* componentArray)
  {
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

      if (dataType.is_valid() && ImGui::CollapsingHeader(propName.data()))
      {
        ImGui::Spacing();
        DataWidget::UseWidget(dataPointer);
        ImGui::Spacing();
      }
    }
  }

  void ComponentWidget::EditSharedComponent(const std::string_view& componentName, SharedComponent* component)
  {
    std::string derivedComponentName = componentName.data();
    derivedComponentName += "*";
    rttr::variant componentPointer = component;
    const rttr::type componentType = rttr::type::get_by_name(derivedComponentName.c_str());

    bool success = componentPointer.convert(componentType);

    if (!success || !ImGui::CollapsingHeader(componentName.data()))
    {
      return;
    }

    ImGui::Spacing();
    DataWidget::UseWidget(componentPointer);
    ImGui::Spacing();
  }
}