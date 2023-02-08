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

namespace Barrage
{
  bool ComponentWidget::UseWidget(const std::string_view& componentName, Component* component)
  {
    if (component == nullptr)
    {
      return false;
    }

    if (component->GetType() == Component::Type::ARRAY)
    {
      return EditComponentArray(componentName, dynamic_cast<ComponentArray*>(component));
    }
    else if (component->GetType() == Component::Type::SHARED)
    {
      return EditSharedComponent(componentName, dynamic_cast<SharedComponent*>(component));
    }

    return false;
  }

  bool ComponentWidget::EditComponentArray(const std::string_view& componentName, ComponentArray* componentArray)
  {
    std::string derivedArrayName = componentName.data();
    derivedArrayName += "*";
    rttr::variant arrayPointer = componentArray;
    const rttr::type arrayType = rttr::type::get_by_name(derivedArrayName.data());

    bool success = arrayPointer.convert(arrayType);

    if (!success)
    {
      return false;
    }

    for (auto& prop : arrayType.get_properties())
    {
      std::string propName = prop.get_name().data();
      
      if (derivedArrayName.find(propName) == std::string::npos)
      {
        continue;
      }

      const rttr::type dataType = rttr::type::get_by_name(propName);
      rttr::variant data = componentArray->GetRTTRValue(0);

      if (dataType.is_valid() && ImGui::CollapsingHeader(propName.data()))
      {
        ImGui::Spacing();
        bool dataChanged = DataWidget::UseWidget(data);
        ImGui::Spacing();

        if (dataChanged)
        {
          componentArray->SetRTTRValue(0, data);
        }

        return dataChanged;
      }
    }

    return false;
  }

  bool ComponentWidget::EditSharedComponent(const std::string_view& componentName, SharedComponent* component)
  {
    std::string derivedComponentName = componentName.data();
    derivedComponentName += "*";
    rttr::variant componentPointer = component;
    const rttr::type componentType = rttr::type::get_by_name(derivedComponentName.data());

    bool success = componentPointer.convert(componentType);

    if (!success || !ImGui::CollapsingHeader(componentName.data()))
    {
      return false;
    }

    ImGui::Spacing();

    bool dataChanged = false;

    for (auto& prop : componentType.get_properties())
    {
      rttr::variant propData = prop.get_value(componentPointer);
      
      if (DataWidget::UseWidget(propData, prop.get_name()))
      {
        dataChanged = true;
        prop.set_value(componentPointer, propData);
      }
    }

    ImGui::Spacing();

    return dataChanged;
  }
}