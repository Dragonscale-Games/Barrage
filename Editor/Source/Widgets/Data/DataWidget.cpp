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
      return function(object, name.data());
    }
    else
    {
      bool objectChanged = false;
      
      if (!treeNode || ImGui::TreeNode(name.data()))
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
    AddDataWidget(rttr::type::get<Sprite>(), SpriteWidget);
  }

  bool DataWidget::FloatWidget(DataWrapper object, const char* name)
  {
    float value = object.GetValue<float>();

    bool fieldChanged = ImGui::DragFloat(name, &value);

    if (fieldChanged)
    {
      object.SetValue(value);
    }

    return fieldChanged;
  }

  bool DataWidget::DoubleWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (double)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::IntWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (int)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedIntWidget(DataWrapper object, const char* name)
  {
    unsigned value = object.GetValue<unsigned>();

    const ImU32 one_step = 1;

    bool fieldChanged = ImGui::InputScalar(name, ImGuiDataType_U32, &value, &one_step);

    if (fieldChanged)
    {
      object.SetValue(value);
    }

    return fieldChanged;
  }

  bool DataWidget::CharWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (char)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedCharWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (uchar)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::ShortWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (short)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedShortWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (ushort)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::LongLongWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (long long)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::UnsignedLongLongWidget(DataWrapper object, const char* name)
  {
    std::string text = name;
    text += " (unsigned long long)";
    ImGui::Text(text.data());
    return false;
  }

  bool DataWidget::StringWidget(DataWrapper object, const char* name)
  {
    std::string value = object.GetValue<std::string>();

    bool fieldChanged = ImGui::InputText(name, &value);

    if (fieldChanged)
    {
      object.SetValue(value);
    }

    return fieldChanged;
  }

  bool DataWidget::RotationWidget(DataWrapper object, const char* name)
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

    return fieldChanged;
  }

  bool DataWidget::SpriteWidget(DataWrapper object, const char* name)
  {
    rttr::type type = rttr::type::get_by_name(name);
    rttr::variant sprite = object.GetValue<Sprite>();

    bool fieldChanged = false;

    for (auto& prop : type.get_properties())
    {
      rttr::string_view propName = prop.get_name();
      rttr::variant propValue = prop.get_value(sprite);

      if (std::string(propName.data()) == "texture" && propValue.is_type<std::string>())
      {
        std::vector<std::string> textureNames = Engine::Instance->GfxRegistry().GetTextureNames();
        std::string currentTexture = propValue.get_value<std::string>();

        if (ImGui::BeginCombo("texture", currentTexture.data()))
        {
          for (auto& textureName : textureNames)
          {
            if (ImGui::Selectable(textureName.data(), textureName == currentTexture))
            {
              fieldChanged = true;
              prop.set_value(sprite, textureName);
            }
          }
          ImGui::EndCombo();
        }
      }
      else
      {
        if (DataWidget::UseWidget(propValue, propName))
        {
          fieldChanged = true;
          prop.set_value(sprite, propValue);
        }
      }
    }

    if (fieldChanged)
    {
      object.SetValue(sprite.get_value<Sprite>());
    }

    return fieldChanged;
  }
}