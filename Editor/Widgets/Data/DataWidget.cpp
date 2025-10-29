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
#include "ComponentArrays/ColorTint/ColorTintArray.hpp"
#include "ComponentArrays/Rotation/RotationArray.hpp"
#include "Components/Sprite/Sprite.hpp"
#include "Objects/Spawning/SpawnRuleFactory.hpp"
#include "Objects/Behavior/BehaviorNodeFactory.hpp"
#include <algorithm>
#include "Objects/Spawning/SpawnLayer.hpp"

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
  IdStringMap DataWidget::spawnRuleAddMap_ = IdStringMap();
  IdStringMap DataWidget::behaviorNodeAddMap_ = IdStringMap();
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
          rttr::variant elementVariant = arrayView.get_value(i).extract_wrapped_value();

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
            arrayView.erase(arrayView.begin() + static_cast<int>(i));
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
        std::vector<std::tuple<rttr::variant, rttr::variant, bool>> updateTuples;

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
            updateTuples.push_back({ key, val, objectValue.chainUndoEnabled_ });
          }

          id++;
        }

        for (auto it = updateTuples.begin(); it != updateTuples.end(); ++it)
        {
          auto& tuple = *it;

          mapView.erase(std::get<0>(tuple));
          mapView.insert(std::get<0>(tuple), std::get<1>(tuple));

          object.valueWasSet_ = true;
          object.chainUndoEnabled_ = std::get<2>(tuple);
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
    AddDataWidget<bool>(BoolWidget);
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
    AddDataWidget<Radian>(AngleWidget);
    AddDataWidget<BehaviorTree>(BehaviorTreeWidget);
    AddDataWidget<ColorTint>(ColorWidget);
    AddDataWidget<SpawnLayer>(SpawnLayerWidget);
    AddDataWidget<Sprite>(SpriteWidget);
  }

  void DataWidget::BoolWidget(DataObject& object)
  {
    bool value = object.GetValue<bool>();

    bool fieldChanged = ImGui::Checkbox(object.GetName().c_str(), &value);

    if (fieldChanged)
    {
      object.SetValue(value);
    }
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
    long long value = object.GetValue<long long>();

    bool fieldChanged = ImGui::DragScalar(object.GetName().c_str(), ImGuiDataType_S64, &value);
    
    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }
    
    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(value);
    }
  }

  void DataWidget::UnsignedLongLongWidget(DataObject& object)
  {
    unsigned long long value = object.GetValue<unsigned long long>();

    bool fieldChanged = ImGui::DragScalar(object.GetName().c_str(), ImGuiDataType_U64, &value);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(value);
    }
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

  void DataWidget::AngleWidget(DataObject& object)
  {
    Radian angleRadians = object.GetValue<Radian>();
    Degree angleDegrees = angleRadians.ToDegrees();

    // just so the user never sees "negative zero" for an angle in the editor
    if (angleDegrees.value_ == -0.0f)
    {
      angleDegrees.value_ = 0.0f;
    }

    bool fieldChanged = ImGui::DragFloat("angle", &angleDegrees.value_);

    if (ImGui::IsItemActive())
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      angleRadians = Radian(angleDegrees);
      object.SetValue(angleRadians);
    }
  }

  bool DataWidget::BehaviorNodeHelper(DataObject& treeObject, DeepPtr<BehaviorNodeRecipe>& nodePtr, size_t id)
  {
    if (!nodePtr->node_)
    {
      LogWidget::AddEntry("Empty behavior node pointer encountered.");
      return true;
    }

    float buttonWidth = ImGui::CalcTextSize("X").x + ImGui::GetStyle().FramePadding.x * 2.0f;

    ImGui::PushID(static_cast<int>(id));
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::BeginGroup();
    ImGui::PushItemWidth(-buttonWidth - 150.0f);
    ImGui::BeginGroup();
    ImGui::Text(nodePtr->node_->GetName().c_str());
    ImGui::Spacing();
    rttr::variant nodeVariant = nodePtr->node_->GetRTTRValue();

    if (nodeVariant.is_valid())
    {
      DataObject nodeObject(nodePtr->node_->GetName(), nodeVariant);

      DataWidget::Use(nodeObject);

      if (nodeObject.ValueWasSet() && !treeObject.ValueWasSet())
      {
        nodePtr->node_->SetRTTRValue(nodeObject.value_);
        treeObject.valueWasSet_ = true;

        if (nodeObject.ChainUndoEnabled())
        {
          treeObject.SetChainUndo(true);
        }
      }

      ImGui::Spacing();
    }

    BehaviorNodeType behaviorNodeType = nodePtr->node_->GetType();

    float padding = 6.0f;

    if (behaviorNodeType != BehaviorNodeType::Action)
    {
      size_t numChildren = nodePtr->children_.size();

      ImGui::Indent(2.0f * padding);

      for (size_t i = 0; i < numChildren; ++i)
      {
        if (BehaviorNodeHelper(treeObject, nodePtr->children_.at(i), i) && !treeObject.ValueWasSet())
        {
          nodePtr->children_.erase(nodePtr->children_.begin() + i);
          treeObject.valueWasSet_ = true;
          break;
        }

        ImGui::Spacing();
      }

      ImGui::Unindent(2.0f * padding);

      if (behaviorNodeType == BehaviorNodeType::Composite ||
        (behaviorNodeType == BehaviorNodeType::Decorator && numChildren == 0) ||
        (behaviorNodeType == BehaviorNodeType::Parallel && numChildren < MAX_PARALLEL_NODE_CHILDREN))
      {
        ImGuiID currentId = ImGui::GetID("Map");

        if (behaviorNodeAddMap_.count(currentId))
        {
          std::string& selectedBehaviorNode = behaviorNodeAddMap_.at(currentId);
          const StringSet& behaviorNodeNames = BehaviorNodeFactory::GetBehaviorNodeNames();

          if (ImGui::BeginCombo("##newBehaviorNode", selectedBehaviorNode.c_str()))
          {
            for (auto& behaviorNodeName : behaviorNodeNames)
            {
              if (ImGui::Selectable(behaviorNodeName.c_str(), behaviorNodeName == selectedBehaviorNode))
              {
                selectedBehaviorNode = behaviorNodeName;
              }
            }
            ImGui::EndCombo();
          }

          ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.6f, 1.0f));
          ImGui::Text("Select behavior node to add.");
          ImGui::PopStyleColor();

          if (ImGui::Button("Confirm") && !treeObject.ValueWasSet())
          {
            DeepPtr<BehaviorNode> newBehaviorNode = BehaviorNodeFactory::CreateBehaviorNode(selectedBehaviorNode);

            if (newBehaviorNode)
            {
              newBehaviorNode->SetRTTRValue(newBehaviorNode->GetRTTRValue());
              nodePtr->children_.push_back(DeepPtr<BehaviorNodeRecipe>(std::make_shared<BehaviorNodeRecipe>(newBehaviorNode)));
              behaviorNodeAddMap_.erase(currentId);
              treeObject.valueWasSet_ = true;
            }
          }
          ImGui::SameLine();
          if (ImGui::Button("Cancel"))
          {
            behaviorNodeAddMap_.erase(currentId);
          }
        }
        else if (ImGui::Button("Add child node"))
        {
          behaviorNodeAddMap_[currentId];
        }
      }
    }

    ImGui::EndGroup();
    ImGui::PopItemWidth();
    ImGui::SameLine();
    if (ImGui::Button("X"))
    {
      ImGui::EndGroup();
      ImGui::PopID();
      return true;
    }

    ImGui::EndGroup();

    ImVec2 itemRectMin = ImGui::GetItemRectMin();
    ImVec2 itemRectMax = ImGui::GetItemRectMax();
    
    itemRectMin.x -= padding;
    itemRectMin.y -= padding;
    itemRectMax.x += padding;
    itemRectMax.y += padding;
    
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddRect(itemRectMin, itemRectMax, IM_COL32(150, 150, 150, 100));

    ImGui::Spacing();

    ImGui::PopID();

    return false;
  }

  void DataWidget::BehaviorTreeWidget(DataObject& object)
  {
    BehaviorTree behaviorTree = object.GetValue<BehaviorTree>();

    if (behaviorTree.recipe_)
    {
      float padding = 6.0f;

      ImGui::Indent(padding);

      if (BehaviorNodeHelper(object, behaviorTree.recipe_, 0) && !object.ValueWasSet())
      {
        behaviorTree.recipe_ = DeepPtr<BehaviorNodeRecipe>();
        object.valueWasSet_ = true;
      }

      ImGui::Unindent(padding);
    }
    else
    {
      ImGuiID currentId = ImGui::GetID("Map");

      if (behaviorNodeAddMap_.count(currentId))
      {
        std::string& selectedBehaviorNode = behaviorNodeAddMap_.at(currentId);
        const StringSet& behaviorNodeNames = BehaviorNodeFactory::GetBehaviorNodeNames();

        if (ImGui::BeginCombo("##newBehaviorNode", selectedBehaviorNode.c_str()))
        {
          for (auto& behaviorNodeName : behaviorNodeNames)
          {
            if (ImGui::Selectable(behaviorNodeName.c_str(), behaviorNodeName == selectedBehaviorNode))
            {
              selectedBehaviorNode = behaviorNodeName;
            }
          }
          ImGui::EndCombo();
        }

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.6f, 1.0f));
        ImGui::Text("Select behavior node to add.");
        ImGui::PopStyleColor();

        if (ImGui::Button("Confirm") && !object.ValueWasSet())
        {
          DeepPtr<BehaviorNode> newBehaviorNode = BehaviorNodeFactory::CreateBehaviorNode(selectedBehaviorNode);

          if (newBehaviorNode)
          {
            newBehaviorNode->SetRTTRValue(newBehaviorNode->GetRTTRValue());
            behaviorTree.recipe_ = DeepPtr<BehaviorNodeRecipe>(std::make_shared<BehaviorNodeRecipe>(newBehaviorNode));
            behaviorNodeAddMap_.erase(currentId);
            object.valueWasSet_ = true;
          }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
          behaviorNodeAddMap_.erase(currentId);
        }
      }
      else if (ImGui::Button("Add root node"))
      {
        behaviorNodeAddMap_[currentId];
      }
    }

    if (object.valueWasSet_)
    {
      object.SetValue(behaviorTree);
    }
  }

  void DataWidget::ColorWidget(DataObject& object)
  {
    ColorTint value = object.GetValue<ColorTint>();

    bool fieldChanged = ImGui::ColorPicker3(object.GetName().c_str(), &value.red_);
    bool itemActive = ImGui::IsItemActive();
    fieldChanged |= ImGui::SliderFloat("alpha", &value.alpha_, 0.0f, 1.0f);
    itemActive |= ImGui::IsItemActive();

    if (itemActive)
    {
      object.SetChainUndo(true);
    }

    if (fieldChanged || ImGui::IsItemDeactivatedAfterEdit())
    {
      object.SetValue(value);
    }
  }

  struct SpawnRulePayload
  {
    size_t index_;
    ImGuiID id_;
  };

  bool DataWidget::SpawnRuleListHelper(DataObject& layerObject, SpawnRuleList& spawnRuleList, int id)
  {
    ImGui::PushID(id);
    
    ImGuiID listId = ImGui::GetID("List");

    bool listChanged = false;

    size_t listSize = spawnRuleList.size();
    float buttonWidth = ImGui::CalcTextSize("X").x + ImGui::GetStyle().FramePadding.x * 2.0f;

    for (size_t i = 0; i < listSize; ++i)
    {
      DeepPtr<SpawnRule>& spawnRule = spawnRuleList[i];

      ImGui::PushID(static_cast<int>(i));
      
      ImGui::Spacing();
      ImGui::Spacing();
      ImGui::BeginGroup();
      ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x - buttonWidth - 150.0f);
      ImGui::BeginGroup();
      ImGui::Text((spawnRule->GetName() + (id == 0 ? " (value)" : " (count)")).c_str());
      if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
      {
        SpawnRulePayload payload{ i, listId };
        ImGui::Text(spawnRule->GetName().c_str());
        ImGui::SetDragDropPayload("SpawnRulePayload", &payload, sizeof(SpawnRulePayload));
        ImGui::EndDragDropSource();
      }
      rttr::variant dataVariant = spawnRule->GetRTTRValue();
      
      if (dataVariant.is_valid())
      {
        DataObject dataObject("##DataObject", dataVariant);
        DataWidget::Use(dataObject);
      
        if (dataObject.ValueWasSet())
        {
          DeepPtr<SpawnRule> newSpawnRule = SpawnRuleFactory::CreateSpawnRule(spawnRule->GetName());
          newSpawnRule->SetRTTRValue(dataVariant);
          spawnRuleList[i] = newSpawnRule;
          listChanged = true;
          layerObject.chainUndoEnabled_ |= dataObject.chainUndoEnabled_;
        }
      }
      ImGui::EndGroup();
      ImGui::PopItemWidth();
      ImGui::SameLine();
      if (ImGui::Button("X"))
      {
        spawnRuleList.erase(spawnRuleList.begin() + i);
        listChanged = true;
        ImGui::EndGroup();
        ImGui::PopID();
        break;
      }

      ImGui::EndGroup();

      if (ImGui::BeginDragDropTarget())
      {
        const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SpawnRulePayload", ImGuiDragDropFlags_AcceptPeekOnly);
        
        if (payload && static_cast<SpawnRulePayload*>(payload->Data)->id_ == listId)
        {
          ImVec2 widgetPos = ImGui::GetItemRectMin();

          // Draw a horizontal line
          ImGui::GetWindowDrawList()->AddLine(
            ImVec2(widgetPos.x, widgetPos.y - 9.0f),               // Start point 
            ImVec2(widgetPos.x + ImGui::GetContentRegionAvail().x - buttonWidth - 150.0f, widgetPos.y - 9.0f),  // End point
            IM_COL32(255, 0, 0, 255),  // Color 
            2.0f                       // Line thickness
          );

          if (payload->IsDelivery() && !listChanged)
          {
            size_t sourceIndex = static_cast<SpawnRulePayload*>(payload->Data)->index_;
            size_t destinationIndex = i;

            bool insertionHappened = false;

            if (sourceIndex < destinationIndex)
            {
              spawnRuleList.insert(spawnRuleList.begin() + destinationIndex, spawnRuleList[sourceIndex]);
              spawnRuleList.erase(spawnRuleList.begin() + sourceIndex);
              insertionHappened = true;
            }
            else if (sourceIndex > destinationIndex)
            {
              spawnRuleList.insert(spawnRuleList.begin() + destinationIndex, spawnRuleList[sourceIndex]);
              spawnRuleList.erase(spawnRuleList.begin() + sourceIndex + 1);
              insertionHappened = true;
            }

            if (insertionHappened)
            {
              listChanged = true;

              ImGui::EndDragDropTarget();
              ImGui::PopID();
              ImGui::PopID();
              return true;
            }
          }
        }
        
        ImGui::EndDragDropTarget();
      }
      
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

    //if (ImGui::BeginDragDropTarget())
    //{
    //  const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SpawnRulePayload", ImGuiDragDropFlags_AcceptPeekOnly);

    //  if (payload && static_cast<SpawnRulePayload*>(payload->Data)->id_ == listId)
    //  {
    //    ImVec2 widgetPos = ImGui::GetItemRectMin();

    //    // Draw a horizontal line
    //    ImGui::GetWindowDrawList()->AddLine(
    //      ImVec2(widgetPos.x, widgetPos.y - 4.0f),               // Start point (a bit above the Text widget)
    //      ImVec2(widgetPos.x + ImGui::GetContentRegionAvail().x - buttonWidth - 150.0f, widgetPos.y - 4.0f),  // End point
    //      IM_COL32(255, 0, 0, 255),  // Color (red in this example)
    //      2.0f                       // Line thickness
    //    );

    //    if (payload->IsDelivery() && !listChanged)
    //    {
    //      size_t sourceIndex = static_cast<SpawnRulePayload*>(payload->Data)->index_;

    //      spawnRuleList.push_back(spawnRuleList[sourceIndex]);
    //      spawnRuleList.erase(spawnRuleList.begin() + sourceIndex);
    //      listChanged = true;
    //    }
    //  }

    //  ImGui::EndDragDropTarget();
    //}

    ImGui::PopID();

    return listChanged;
  }

  void DataWidget::SpawnLayerWidget(DataObject& object)
  {
    SpawnLayer spawnLayer = object.GetValue<SpawnLayer>();
    bool fieldChanged = false;

    const ImU32 one_step = 1;
    fieldChanged |= ImGui::InputScalar("count", ImGuiDataType_U32, &spawnLayer.baseNumGroups_, &one_step);

    if (ImGui::TreeNodeEx("spawnRules", ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen))
    {
      fieldChanged |= SpawnRuleListHelper(object, spawnLayer.valueRules_, 0);
      fieldChanged |= SpawnRuleListHelper(object, spawnLayer.countRules_, 1);

      ImGui::Spacing();

      ImGuiID currentId = ImGui::GetID("Map");

      if (spawnRuleAddMap_.count(currentId))
      {
        std::string& selectedSpawnRule = spawnRuleAddMap_.at(currentId);
        const StringSet& spawnRuleNames = SpawnRuleFactory::GetSpawnRuleNames();

        if (ImGui::BeginCombo("##newSpawnRule", selectedSpawnRule.c_str()))
        {
          for (auto& spawnRuleName : spawnRuleNames)
          {
            if (ImGui::Selectable(spawnRuleName.c_str(), spawnRuleName == selectedSpawnRule))
            {
              selectedSpawnRule = spawnRuleName;
            }
          }
          ImGui::EndCombo();
        }

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.6f, 1.0f));
        ImGui::Text("Select spawn rule to add.");
        ImGui::PopStyleColor();

        if (ImGui::Button("Confirm"))
        {
          DeepPtr<SpawnRule> newSpawnRule = SpawnRuleFactory::CreateSpawnRule(selectedSpawnRule);

          if (newSpawnRule)
          {
            newSpawnRule->SetRTTRValue(newSpawnRule->GetRTTRValue());

            SpawnRuleStage stage = newSpawnRule->GetStage();
            if (stage == SpawnRuleStage::VALUE_RULE)
            {
              spawnLayer.valueRules_.push_back(newSpawnRule);
              fieldChanged = true;
            }
            else if (stage == SpawnRuleStage::COUNT_RULE)
            {
              spawnLayer.countRules_.push_back(newSpawnRule);
              fieldChanged = true;
            }

            spawnRuleAddMap_.erase(currentId);
          }
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel") && !object.valueWasSet_)
        {
          spawnRuleAddMap_.erase(currentId);
        }
      }
      else
      {
        ImGui::BeginGroup();

        if (ImGui::Button("Add new rule") && !object.valueWasSet_)
        {
          spawnRuleAddMap_[currentId];
        }
        ImGui::EndGroup();
      }

      ImGui::TreePop();
    }

    if (fieldChanged)
    {
      object.SetValue(spawnLayer);
    }
  }

  void DataWidget::SpriteWidget(DataObject& object)
  {
    Sprite sprite = object.GetValue<Sprite>();
    bool fieldChanged = false;

    std::vector<std::string> textureNames = Engine::Get().Graphics().Textures().GetTextureNames();

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
    fieldChanged |= ImGui::InputScalar("cols", ImGuiDataType_U32, &sprite.cols_, &one_step);
    fieldChanged |= ImGui::InputScalar("rows", ImGuiDataType_U32, &sprite.rows_, &one_step);

    if (sprite.cols_ == 0)
    {
      sprite.cols_ = 1;
    }

    if (sprite.rows_ == 0)
    {
      sprite.rows_ = 1;
    }

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