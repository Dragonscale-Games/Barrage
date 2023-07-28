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
#include <Editor.hpp>
#include "ComponentArrays/RotationArray.hpp"
#include "Components/Sprite.hpp"

namespace Barrage
{
  DataWidget::DataObject::DataObject(const std::string& name, rttr::variant& value) :
    name_(name),
    value_(value),
    valueWasSet_(false),
    chainUndoEnabled_(false)
  {
  }

  const std::string& DataWidget::DataObject::GetName()
  {
    return name_;
  }

  rttr::variant DataWidget::DataObject::GetRTTRValue()
  {
    return value_;
  }

  void DataWidget::DataObject::SetChainUndo(bool enable)
  {
    chainUndoEnabled_ = enable;
  }

  bool DataWidget::DataObject::ChainUndoEnabled()
  {
    return chainUndoEnabled_;
  }

  bool DataWidget::DataObject::ValueWasSet()
  {
    return valueWasSet_;
  }
  
  DataWidget::DataWidgetFunctionMap DataWidget::widgetFunctions_ = DataWidget::DataWidgetFunctionMap();
  IdVariantMap DataWidget::keyEditorMap_ = IdVariantMap();
  bool DataWidget::initialized_ = false;
  
  void DataWidget::Use(DataObject& object, bool treeNode)
  {
    if (!initialized_)
    {
      Initialize();
      initialized_ = true;
    }

    rttr::type objectType = object.value_.get_type();

    if (!objectType.is_valid())
    {
      ImGui::Text("Error: Unregistered type");
      return;
    }
    else if (objectType.is_wrapper())
    {
      objectType = objectType.get_wrapped_type();
      object.value_ = object.value_.extract_wrapped_value();
    }

    std::string typeName = objectType.get_name().data();

    if (object.name_.empty())
    {
      object.name_ = typeName;
    }

    ImGui::PushID(object.name_.c_str());

    if (widgetFunctions_.find(typeName) != widgetFunctions_.end())
    {
      DataWidgetFunction function = widgetFunctions_.at(typeName);
      function(object);
    }
    else if (!treeNode || ImGui::TreeNodeEx(object.name_.c_str(), ImGuiTreeNodeFlags_SpanAvailWidth))
    {
      if (objectType.is_sequential_container())
      {
        rttr::variant_sequential_view arrayView = object.value_.create_sequential_view();

        size_t arraySize = arrayView.get_size();

        for (size_t i = 0; i < arraySize; ++i)
        {
          rttr::variant elementVariant = arrayView.get_value(i);

          DataObject elementObject("##ElementObject", elementVariant);

          ImGui::PushID(static_cast<int>(i));
          ImGui::Spacing();
          ImGui::Spacing();
          ImGui::BeginGroup();
          float buttonWidth = ImGui::CalcTextSize("X").x + ImGui::GetStyle().FramePadding.x * 2.0f;
          ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - buttonWidth - 150.0f);
          ImGui::BeginGroup();
          DataWidget::Use(elementObject);
          ImGui::EndGroup();
          ImGui::PopItemWidth();
          ImGui::SameLine();
          if (ImGui::Button("X"))
          {
            arrayView.erase(arrayView.begin() + i);
            object.valueWasSet_ = true;
            ImGui::EndGroup();
            ImGui::PopID();
            break;
          }
          else if (elementObject.ValueWasSet())
          {
            arrayView.set_value(i, elementObject.value_);
            object.valueWasSet_ = true;
            object.chainUndoEnabled_ = elementObject.chainUndoEnabled_;
          }
          ImGui::EndGroup();

          ImVec2 itemRectMin = ImGui::GetItemRectMin();
          ImVec2 itemRectMax = ImGui::GetItemRectMax();

          float padding = 6.0f;

          itemRectMin.x -= padding;
          itemRectMin.y -= padding;
          itemRectMax.x += padding;
          itemRectMax.y += padding;

          ImDrawList* drawList = ImGui::GetWindowDrawList();
          drawList->AddRect(itemRectMin, itemRectMax, IM_COL32(150, 150, 150, 100));

          ImGui::Spacing();

          ImGui::PopID();
        }

        ImGui::Spacing();

        if (ImGui::Button("Add new") && !object.valueWasSet_)
        {
          size_t arraySize = arrayView.get_size();
          if (arrayView.set_size(arraySize + 1))
          {
            object.valueWasSet_ = true;
          }
        }

        ImGui::Spacing();
      }
      else if (objectType.is_associative_container())
      {
        rttr::variant_associative_view mapView = object.value_.create_associative_view();
        rttr::type mapKeyType = mapView.get_key_type();

        ImGuiID currentId = ImGui::GetID("Map");

        unsigned id = 0;
          
        for (auto& element : mapView)
        {
          rttr::variant key = element.first.extract_wrapped_value();
          rttr::variant val = element.second.extract_wrapped_value();
          DataObject objectKey("##Key", key);
          DataObject objectValue("##Value", val);

          ImGui::PushID(id);
          ImGui::Spacing();
          ImGui::Spacing();
          ImGui::BeginGroup();
          float buttonWidth = ImGui::CalcTextSize("X").x + ImGui::GetStyle().FramePadding.x * 2.0f;
          ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - buttonWidth - 150.0f);
          ImGui::BeginGroup();
          ImGui::Text("Key:");
          ImGui::Spacing();
          DataWidget::Use(objectKey);
          ImGui::Spacing();
          ImGui::Text("Value:");
          ImGui::Spacing();
          DataWidget::Use(objectValue);
          ImGui::EndGroup();
          ImGui::PopItemWidth();
          ImGui::SameLine();
          bool elementRemoved = ImGui::Button("X");
          ImGui::EndGroup();
          ImGui::PopID();

          ImVec2 itemRectMin = ImGui::GetItemRectMin();
          ImVec2 itemRectMax = ImGui::GetItemRectMax();

          float padding = 6.0f;

          itemRectMin.x -= padding;
          itemRectMin.y -= padding;
          itemRectMax.x += padding;
          itemRectMax.y += padding;

          ImDrawList* drawList = ImGui::GetWindowDrawList();
          drawList->AddRect(itemRectMin, itemRectMax, IM_COL32(150, 150, 150, 100));

          ImGui::Spacing();

          if (elementRemoved)
          {
            mapView.erase(key);
            object.valueWasSet_ = true;
            break;
          }
          else if (objectKey.ValueWasSet() && mapView.find(key) == mapView.end())
          {
            rttr::variant oldKey = element.first.extract_wrapped_value();
            rttr::variant storedValue = element.second.extract_wrapped_value();
            
            mapView.erase(oldKey);
            mapView.insert(key, storedValue);
            
            object.valueWasSet_ = true;
            object.chainUndoEnabled_ = objectKey.chainUndoEnabled_;
            
            break;
          }
          else if (objectValue.ValueWasSet())
          {
            mapView.erase(key);
            mapView.insert(key, val);

            object.valueWasSet_ = true;
            object.chainUndoEnabled_ = objectValue.chainUndoEnabled_;

            break;
          }

          id++;
        }

        ImGui::Spacing();

        if (keyEditorMap_.count(currentId))
        {
          rttr::variant& keyVariant = keyEditorMap_.at(currentId);
          rttr::type keyVariantType = keyVariant.get_type();
          DataObject newKey("(" + std::string(keyVariantType.get_name().data()) + ")", keyVariant);
          DataWidget::Use(newKey);

          bool keyExists = (mapView.find(keyVariant) != mapView.end());

          ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.6f, 1.0f));
          if (keyExists)
          {
            ImGui::Text("Enter new key value. (Key already exists.)");
          }
          else
          {
            ImGui::Text("Enter new key value.");
          }
          ImGui::PopStyleColor();

          if (ImGui::Button("Confirm") && !keyExists && keyVariant.get_type() == mapKeyType && !object.valueWasSet_)
          {
            if (mapView.get_value_type().is_valid() && mapView.get_value_type().get_constructor().is_valid())
            {
              if (mapView.insert(keyVariant, mapView.get_value_type().create()).second)
              {
                object.valueWasSet_ = true;
                keyEditorMap_.erase(currentId);
              }
            }
          }
          ImGui::SameLine();
          if (ImGui::Button("Cancel") && !object.valueWasSet_)
          {
            keyEditorMap_.erase(currentId);
          }
        }
        else
        {
          if (ImGui::Button("Add new") && !object.valueWasSet_)
          {
            if (mapKeyType == rttr::type::get<int>())
            {
              int defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<unsigned>())
            {
              unsigned defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<char>())
            {
              char defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<unsigned char>())
            {
              unsigned char defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<short>())
            {
              short defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<unsigned short>())
            {
              unsigned short defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<long long>())
            {
              long long defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<unsigned long long>())
            {
              unsigned long long defaultValue = 0;
              keyEditorMap_[currentId] = defaultValue;
            }
            else if (mapKeyType == rttr::type::get<std::string>())
            {
              std::string defaultValue;
              keyEditorMap_[currentId] = defaultValue;
            }
          }
        }
        
        ImGui::Spacing();
      }
      else if (typeName.back() == '*')
      {
        ImGui::Text("Can't edit pointer type.");
      }
      else
      {
        for (auto& prop : objectType.get_properties())
        {
          rttr::variant property = prop.get_value(object.value_);
          DataObject propObject(prop.get_name().data(), property);
          
          DataWidget::Use(propObject, true);
          
          if (propObject.ValueWasSet())
          {
            prop.set_value(object.value_, propObject.value_);
            object.valueWasSet_ = true;
            object.chainUndoEnabled_ = propObject.chainUndoEnabled_;
          }
        }
      }

      if (treeNode)
      {
        ImGui::TreePop();
      }
    }

    ImGui::PopID();
  }

  void DataWidget::Initialize()
  {
    AddDataWidget<float>(FloatWidget);
    AddDataWidget<double>(DoubleWidget);
    AddDataWidget<int>(IntWidget);
    AddDataWidget<unsigned>(UnsignedIntWidget);
    AddDataWidget<char>(CharWidget);
    AddDataWidget<unsigned char>(UnsignedCharWidget);
    AddDataWidget<short>(ShortWidget);
    AddDataWidget<unsigned short>(UnsignedShortWidget);
    AddDataWidget<long long>(LongLongWidget);
    AddDataWidget<unsigned long long>(UnsignedLongLongWidget);
    AddDataWidget<std::string>(StringWidget);
    AddDataWidget<Rotation>(RotationWidget);
    AddDataWidget<Sprite>(SpriteWidget);
  }

  void DataWidget::FloatWidget(DataObject& object)
  {
    float value = object.GetValue<float>();

    bool fieldChanged = ImGui::DragFloat(object.GetName().c_str(), &value);

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

    bool fieldChanged = ImGui::DragScalar(object.GetName().c_str(), ImGuiDataType_Double, &value);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(value);
    }
  }

  void DataWidget::IntWidget(DataObject& object)
  {
    int value = object.GetValue<int>();

    bool fieldChanged = ImGui::DragInt(object.GetName().c_str(), &value);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(value);
    }
  }

  void DataWidget::UnsignedIntWidget(DataObject& object)
  {
    unsigned value = object.GetValue<unsigned>();

    const ImU32 one_step = 1;

    bool fieldChanged = ImGui::InputScalar(object.GetName().c_str(), ImGuiDataType_U32, &value, &one_step);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(value);
    }
  }

  void DataWidget::CharWidget(DataObject& object)
  {
    std::string text = object.GetName();
    text += " (char)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::UnsignedCharWidget(DataObject& object)
  {
    std::string text = object.GetName();
    text += " (uchar)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::ShortWidget(DataObject& object)
  {
    std::string text = object.GetName();
    text += " (short)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::UnsignedShortWidget(DataObject& object)
  {
    std::string text = object.GetName();
    text += " (ushort)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::LongLongWidget(DataObject& object)
  {
    std::string text = object.GetName();
    text += " (long long)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::UnsignedLongLongWidget(DataObject& object)
  {
    std::string text = object.GetName();
    text += " (unsigned long long)";
    ImGui::Text(text.c_str());
  }

  void DataWidget::StringWidget(DataObject& object)
  {
    std::string value = object.GetValue<std::string>();

    bool fieldChanged = ImGui::InputText(object.GetName().c_str(), &value);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
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
    
    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      rotation.angle_ = -angleDeg * (2 * IM_PI) / 360.0f;
      object.SetValue(rotation);
    }
  }

  void DataWidget::SpriteWidget(DataObject& object)
  {
    Sprite sprite = object.GetValue<Sprite>();

    bool fieldChanged = false;

    std::vector<std::string> textureNames = Engine::Instance->Graphics().Textures().GetTextureNames();

    if (ImGui::BeginCombo("texture", sprite.texture_.c_str()))
    { 
      for (auto& textureName : textureNames)
      {
        if (ImGui::Selectable(textureName.data(), textureName == sprite.texture_))
        {
          fieldChanged = true;
          sprite.texture_ = textureName;
        }
      }
      ImGui::EndCombo();
    }

    const ImU32 one_step = 1;

    fieldChanged |= ImGui::InputScalar("layer", ImGuiDataType_U32, &sprite.layer_, &one_step);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }
    
    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(sprite);
    }
  }
}