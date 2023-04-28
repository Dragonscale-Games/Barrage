/* ======================================================================== */
/*!
 * \file            ComponentArrayWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit the values of a component array.
 */
 /* ======================================================================== */

#include "ComponentArrayWidget.hpp"
#include "Widgets/Data/DataWidget.hpp"
#include <iostream>
#include "Widgets/Popups/ComponentArray/ComponentArrayPopupWidget.hpp"
#include "Commands/Edit/ComponentArray/EditComponentArray.hpp"
#include "Editor/Editor.hpp"

namespace Barrage
{
  void ComponentArrayWidget::Use(const std::string_view& componentName, ComponentArray* componentArray)
  {
    if (componentArray == nullptr)
    {
      return;
    }

    ImGui::PushID(componentName.data());

    bool headerOpen = ImGui::CollapsingHeader(componentName.data());

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      ImGui::OpenPopup("Component Array Popup");
    }

    if (headerOpen)
    {
      rttr::variant value = componentArray->GetRTTRValue(0);
      DataWidget::DataObject object(componentName.data(), value);

      ImGui::Spacing();
      DataWidget::Use(object);
      ImGui::Spacing();

      if (object.ValueWasSet())
      {
        EditorData& editorData = Editor::Instance->Data();
        EditComponentArray* command = new EditComponentArray(
          editorData.selectedScene_, 
          editorData.selectedPool_,
          editorData.selectedObject_,
          componentName,
          object.GetRTTRValue(),
          object.ChainUndoEnabled());
        Editor::Instance->Command().Send(command);
      }
    }

    ComponentArrayPopupWidget::Use("Component Array Popup", componentName);

    ImGui::PopID();
  }
}