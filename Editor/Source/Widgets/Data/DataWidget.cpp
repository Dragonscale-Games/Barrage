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

namespace Barrage
{
  DataWidgetFunctionMap DataWidget::widgetFunctions_ = DataWidgetFunctionMap();
  bool DataWidget::initialized_ = false;
  
  bool DataWidget::UseWidget(rttr::variant& object, rttr::string_view name, bool treeNode)
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
      return false;
    }

    if (name.empty())
    {
      name = object.get_type().get_name();
    }

    std::string typeName = objectType.get_name().data();

    if (widgetFunctions_.find(typeName) != widgetFunctions_.end())
    {
      DataWidgetFunction function = widgetFunctions_.at(typeName);
      return function(object, name);
    }
    else
    {
      bool objectChanged = false;
      
      if (!treeNode || ImGui::TreeNode(objectType.get_name().data()))
      {
        for (auto& prop : objectType.get_properties())
        {
          rttr::variant property = prop.get_value(object);

          bool propertyChanged = UseWidget(property, prop.get_name(), true);
          objectChanged |= propertyChanged;

          if (propertyChanged)
          {
            prop.set_value(object, property);
          }
        }

        if (treeNode)
        {
          ImGui::TreePop();
        }
      }

      return objectChanged;
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

  bool DataWidget::FloatWidget(rttr::variant& object, rttr::string_view name)
  {
    float value = object.get_value<float>();

    bool fieldChanged = ImGui::DragFloat(name.data(), &value);

    if (fieldChanged)
    {
      object = value;
    }

    return fieldChanged;
  }

  bool DataWidget::DoubleWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (double)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::IntWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (int)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedIntWidget(rttr::variant& object, rttr::string_view name)
  {
    unsigned value = object.get_value<unsigned>();

    const ImU32 one_step = 1;

    bool fieldChanged = ImGui::InputScalar(name.data(), ImGuiDataType_U32, &value, &one_step);

    if (fieldChanged)
    {
      object = value;
    }

    return fieldChanged;
  }

  bool DataWidget::CharWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (char)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedCharWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (uchar)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::ShortWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (short)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedShortWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (ushort)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::LongLongWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (long long)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedLongLongWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (unsigned long long)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::StringWidget(rttr::variant& object, rttr::string_view name)
  {
    std::string text = name.data();
    text += " (string)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::RotationWidget(rttr::variant& object, rttr::string_view name)
  {
    Rotation rotation = object.get_value<Rotation>();

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
      object = rotation;
    }

    return fieldChanged;
  }
}