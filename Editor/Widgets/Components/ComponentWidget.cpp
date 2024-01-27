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
#include "Widgets/Data/DataWidget.hpp"
#include <iostream>
#include "Widgets/Popups/Component/ComponentPopupWidget.hpp"
#include <Editor.hpp>
#include "Commands/Edit/Component/EditComponent.hpp"

namespace Barrage
{
  void ComponentWidget::Use(const std::string& componentName, ComponentDeepPtr& component)
  {
    ImGui::PushID(componentName.c_str());

    bool headerOpen = ImGui::CollapsingHeader(componentName.c_str());

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      ImGui::OpenPopup("Component Popup");
    }

    if (headerOpen)
    {
      rttr::variant value = component->GetRTTRValue();
      DataWidget::DataObject object(componentName.c_str(), value);
      
      ImGui::Spacing();
      DataWidget::Use(object);
      ImGui::Spacing();

      if (object.ValueWasSet())
      {
        EditorData& editorData = Editor::Get().Data();
        Editor::Get().Command().Send(std::make_shared<EditComponent>(
          editorData.selectedScene_,
          editorData.selectedPool_,
          componentName,
          object.GetRTTRValue(),
          object.ChainUndoEnabled()
        ));
      }
    }

    ComponentPopupWidget::Use("Component Popup", componentName);

    ImGui::PopID();
  }
}