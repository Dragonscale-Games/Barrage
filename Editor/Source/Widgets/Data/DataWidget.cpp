/* ======================================================================== */
/*!
 * \file            DataWidget.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shows a widget that allows the user to edit a field on an object
   registered with RTTR.
 */
 /* ======================================================================== */

#include "DataWidget.hpp"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_stdlib.h"
#include <Editor/Editor.hpp>

namespace Barrage
{
  DataWidgetFunctionMap DataWidget::widgetFunctions_ = DataWidgetFunctionMap();
  bool DataWidget::initialized_ = false;
  
  void DataWidget::UseWidget(rttr::variant& object, rttr::string_view name, bool treeNode)
  {
    if (!initialized_)
    {
      Initialize();
      initialized_ = true;
    }

    rttr::type objectType = object.get_type();
    
    if (!objectType.is_valid())
    {
      ImGui::Text("Error: Unregistered type");
      return;
    }

    std::string typeName = objectType.get_name().data();

    if (typeName.back() == '*')
    {
      typeName.pop_back();
    }

    if (name.empty())
    {
      name = typeName;
    }

    if (widgetFunctions_.find(typeName) != widgetFunctions_.end())
    {
      DataWidgetFunction function = widgetFunctions_.at(typeName);
      DataObject* dataObject = new DataObject(name.data(), object);
      function(*dataObject);

      if (dataObject->ValueWasSet())
      {
        Editor::Instance->Command().Add(dataObject);
      }
      else
      {
        delete dataObject;
      }
    }
    else if (!treeNode || ImGui::TreeNode(name.data()))
    {
      for (auto& prop : objectType.get_properties())
      {
        rttr::variant property = prop.get_value(object);

        UseWidget(property, prop.get_name(), true);;
      }

      if (treeNode)
      {
        ImGui::TreePop();
      }
    }
  }

  void DataWidget::AddDataWidget(const rttr::type& type, DataWidgetFunction widgetFunction)
  {
    if (!type.is_valid())
    {
      return;
    }
    
    std::string typeName = type.get_name().data();
    widgetFunctions_[typeName] = widgetFunction;
  }

  void DataWidget::Initialize()
  {
    AddDataWidget(rttr::type::get<float>(), FloatWidget);
    AddDataWidget(rttr::type::get<double>(), DoubleWidget);
    AddDataWidget(rttr::type::get<int>(), IntWidget);
    AddDataWidget(rttr::type::get<unsigned>(), UnsignedIntWidget);
    AddDataWidget(rttr::type::get<char>(), CharWidget);
    AddDataWidget(rttr::type::get<unsigned char>(), UnsignedCharWidget);
    AddDataWidget(rttr::type::get<short>(), ShortWidget);
    AddDataWidget(rttr::type::get<unsigned short>(), UnsignedShortWidget);
    AddDataWidget(rttr::type::get<long long>(), LongLongWidget);
    AddDataWidget(rttr::type::get<unsigned long long>(), UnsignedLongLongWidget);
    AddDataWidget(rttr::type::get<std::string>(), StringWidget);
    AddDataWidget(rttr::type::get<Rotation>(), RotationWidget);
  }

  void DataWidget::FloatWidget(DataObject& object)
  {
    float value = object.GetValue<float>();

    bool fieldChanged = ImGui::DragFloat(object.GetValueName().c_str(), &value);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(value);
    }
  }

  void DataWidget::DoubleWidget(DataObject& object)
  {
    double value = object.GetValue<double>();

    bool fieldChanged = ImGui::DragScalar(object.GetValueName().c_str(), ImGuiDataType_Double, &value);

    if (fieldChanged)
    {
      object.SetValue(value);
    }
  }

  void DataWidget::IntWidget(DataObject& object)
  {
    int value = object.GetValue<int>();

    bool fieldChanged = ImGui::DragInt(object.GetValueName().c_str(), &value);

    if (fieldChanged)
    {
      object.SetValue(value);
    }
  }

  void DataWidget::UnsignedIntWidget(DataObject& object)
  {
    unsigned value = object.GetValue<unsigned>();

    const ImU32 one_step = 1;

    bool fieldChanged = ImGui::InputScalar(object.GetValueName().c_str(), ImGuiDataType_U32, &value, &one_step);

    if (fieldChanged)
    {
      object.SetValue(value);
    }
  }

  void DataWidget::CharWidget(DataObject& object)
  {
    std::string text = object.GetValueName();
    text += " (char)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::UnsignedCharWidget(DataObject& object)
  {
    std::string text = object.GetValueName();
    text += " (uchar)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::ShortWidget(DataObject& object)
  {
    std::string text = object.GetValueName();
    text += " (short)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::UnsignedShortWidget(DataObject& object)
  {
    std::string text = object.GetValueName();
    text += " (ushort)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::LongLongWidget(DataObject& object)
  {
    std::string text = object.GetValueName();
    text += " (long long)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::UnsignedLongLongWidget(DataObject& object)
  {
    std::string text = object.GetValueName();
    text += " (unsigned long long)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::StringWidget(DataObject& object)
  {
    std::string value = object.GetValue<std::string>();

    bool fieldChanged = ImGui::InputText(object.GetValueName().c_str(), &value);

    if (fieldChanged)
    {
      object.SetValue(value);
    }
  }

  void DataWidget::RotationWidget(DataObject& object)
  {
    Rotation rotation = object.GetValue<Rotation>();

    float angleDeg = -rotation.angle_ * 360.0f / (2 * IM_PI);

    // just so the user never sees "negative zero" in the editor
    if (angleDeg == -0.0f)
    {
      angleDeg = 0.0f;
    }

    bool fieldChanged = ImGui::DragFloat("angle", &angleDeg);
    
    if (fieldChanged)
    {
      rotation.angle_ = -angleDeg * (2 * IM_PI) / 360.0f;
      object.SetValue(rotation);
    }
  }
}