/* ======================================================================== */
/*!
 * \file            SharedComponentWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit the values of a shared component.
 */
 /* ======================================================================== */

#include "SharedComponentWidget.hpp"
#include "Widgets/Data/DataWidget.hpp"
#include <iostream>
#include "Widgets/Popups/SharedComponent/SharedComponentPopupWidget.hpp"
#include <Editor/Editor.hpp>
#include "Commands/Edit/SharedComponent/EditSharedComponent.hpp"

namespace Barrage
{
  void SharedComponentWidget::Use(const std::string_view& componentName, SharedComponent* sharedComponent)
  {
    if (sharedComponent == nullptr)
    {
      return;
    }

    ImGui::PushID(componentName.data());

    bool headerOpen = ImGui::CollapsingHeader(componentName.data());

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      ImGui::OpenPopup("Shared Component Popup");
    }

    if (headerOpen)
    {
      rttr::variant value = sharedComponent->GetRTTRValue();
      DataWidget::DataObject object(componentName.data(), value);
      
      ImGui::Spacing();
      DataWidget::Use(object);
      ImGui::Spacing();

      if (object.ValueWasSet())
      {
        EditorData& editorData = Editor::Instance->Data();
        EditSharedComponent* command = new EditSharedComponent(
          editorData.selectedScene_,
          editorData.selectedPool_,
          componentName,
          object.GetRTTRValue(),
          object.ChainUndoEnabled());
        Editor::Instance->Command().Send(command);
      }
    }

    SharedComponentPopupWidget::Use("Shared Component Popup", componentName);

    ImGui::PopID();
  }
}