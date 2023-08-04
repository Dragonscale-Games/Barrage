/* ======================================================================== */
/*!
 * \file            DataWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shows a widget that allows the user to edit an object or primitive that's
   registered with RTTR.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DataWidget_BARRAGE_H
#define DataWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <rttr/variant.h>
#include <unordered_map>
#include <imgui/imgui.h>

namespace Barrage
{
  typedef std::unordered_map<ImGuiID, rttr::variant> IdVariantMap;
  
  //! Allows user to edit the values of an RTTR-registered object
  class DataWidget
  {
    public:
      //! Provides a clean interface for editing a value
      class DataObject
      {
        public:
          DataObject(const std::string& name, rttr::variant& value);

          const std::string& GetName();

          rttr::variant GetRTTRValue();

          template <typename T>
          T GetValue();

          template <typename T>
          void SetValue(const T& newValue);

          void SetChainUndo(bool enable);

          bool ChainUndoEnabled();

          bool ValueWasSet();

        private:
          std::string name_;
          rttr::variant& value_;
          bool valueWasSet_;
          bool chainUndoEnabled_;

        friend class DataWidget;
      };

      typedef void (*DataWidgetFunction)(DataObject& object);
      typedef std::unordered_map<std::string, DataWidgetFunction> DataWidgetFunctionMap;

      /**************************************************************/
      /*!
        \brief
          Allows the user to edit a value whose type is registered 
          with RTTR.

        \param name
          The name of the value being edited.

        \param object
          An rttr::variant containing the object/primitive to be
          edited. If the variant contains a pointer, the object or
          primitive it points at is edited instead.

        \param treeNode
          If "true", wraps the class's widgets in a ImGui::TreeNode.
          If "false", displays widgets normally.
          This is generally used internally when this function is
          called recursively on sub-objects of the user object.
      */
      /**************************************************************/
      static void Use(DataObject& object, bool treeNode = false);

      /**************************************************************/
      /*!
        \brief
          Allows the user to edit a value whose type is registered 
          with RTTR.

        \param object
          The object or primitive to be edited.

        \param name
          The name of the object or primitive being edited.

        \param treeNode
          If "true", wraps the class's widgets in a ImGui::TreeNode.
          If "false", displays widgets normally.
      */
      /**************************************************************/
      template <typename T>
      static void Use(T& object, const std::string& name = std::string(), bool treeNode = false);

      /**************************************************************/
      /*!
        \brief
          Allows the user to provide a custom widget for a type 
          registered with RTTR. This will overwrite any widget 
          previously assigned to that type.

        \tparam T
          The type to assign a new widget to.

        \param function
          The custom widget function to add. 
      */
      /**************************************************************/
      template <typename T>
      static void AddDataWidget(DataWidgetFunction widgetFunction);

      static void FloatWidget(DataObject& object);
             
      static void DoubleWidget(DataObject& object);
             
      static void IntWidget(DataObject& object);
             
      static void UnsignedIntWidget(DataObject& object);
             
      static void CharWidget(DataObject& object);
             
      static void UnsignedCharWidget(DataObject& object);
             
      static void ShortWidget(DataObject& object);
             
      static void UnsignedShortWidget(DataObject& object);
             
      static void LongLongWidget(DataObject& object);
             
      static void UnsignedLongLongWidget(DataObject& object);
             
      static void StringWidget(DataObject& object);

      static void AngleWidget(DataObject& object);

      static void SpawnRuleListWidget(DataObject& object);
                 
      static void SpriteWidget(DataObject& object);

    private:
      /**************************************************************/
      /*!
        \brief
          Sets up the function map with the default widget functions
          for primitives and other common/important types.
      */
      /**************************************************************/
      static void Initialize();

    private:
      static DataWidgetFunctionMap widgetFunctions_;
      static IdVariantMap keyEditorMap_;
      static bool initialized_;
  };
}

#include "DataWidget.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // DataWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////