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

#include "Widgets/Widget.hpp"
#include "Commands/ChangeValue/ChangeValue.hpp"

#include <unordered_map>

namespace Barrage
{
  typedef ChangeValue DataObject;
  typedef void (*DataWidgetFunction)(DataObject& object);
  typedef std::unordered_map<std::string, DataWidgetFunction> DataWidgetFunctionMap;

  //! Allows user to edit the values of an RTTR-registered object
  class DataWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds a widget to the window that allows the user to edit
          an object or primitive registered with RTTR.

        \param name
          The name of the object or primitive being edited.

        \param object
          The object or primitive being edited.

        \param treeNode
          If "true", wraps the class's widgets in a ImGui::TreeNode.
          If "false", displays widgets normally.
          This is generally used internally when this function is
          called recursively on sub-objects of the user object.

        \return
          Returns true if the object's value changed, returns false
          otherwise.
      */
      /**************************************************************/
      static void UseWidget(rttr::variant& object, rttr::string_view name = rttr::string_view(), bool treeNode = false);

      /**************************************************************/
      /*!
        \brief
          Allows the user to provide a widget for an object or
          primitive type registered with RTTR. This will overwrite any 
          widget previously assigned to that type.

        \param type
          The rttr::type to assign a new widget to.

        \param function
          The custom widget function to add. 
      */
      /**************************************************************/
      static void AddDataWidget(const rttr::type& type, DataWidgetFunction widgetFunction);

    private:
      /**************************************************************/
      /*!
        \brief
          Sets up the function map with the default widget functions
          for primitives and other common/important types.
      */
      /**************************************************************/
      static void Initialize();

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

      static void RotationWidget(DataObject& object);

    private:
      static DataWidgetFunctionMap widgetFunctions_;
      static bool initialized_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DataWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////