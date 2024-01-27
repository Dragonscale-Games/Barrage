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
#include "Editor.hpp"

namespace Barrage
{
  void ComponentArrayWidget::Use(const std::string& componentName, ComponentArrayDeepPtr& componentArray)
  {
    ImGui::PushID(componentName.c_str());

    bool headerOpen = ImGui::CollapsingHeader(componentName.c_str());

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
    {
      ImGui::OpenPopup("Component Array Popup");
    }

    if (headerOpen)
    {
      rttr::variant value = componentArray->GetRTTRValue(0);
      DataWidget::DataObject object(componentName.c_str(), value);

      ImGui::Spacing();
      DataWidget::Use(object);
      ImGui::Spacing();

      if (object.ValueWasSet())
      {
        EditorData& editorData = Editor::Get().Data();
        
        bool isSpawnArchetype = false;

        if (!editorData.selectedSpawnArchetype_.empty())
        {
          isSpawnArchetype = true;
        }

        Editor::Get().Command().Send(std::make_shared<EditComponentArray>(
          editorData.selectedScene_,
          editorData.selectedPool_,
          isSpawnArchetype ? editorData.selectedSpawnArchetype_ : editorData.selectedStartingObject_,
          componentName,
          isSpawnArchetype,
          object.GetRTTRValue(),
          object.ChainUndoEnabled()
        ));
      }
    }

    ComponentArrayPopupWidget::Use("Component Array Popup", componentName);

    ImGui::PopID();
  }
}