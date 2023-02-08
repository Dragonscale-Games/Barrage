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
#include <unordered_map>

namespace Barrage
{
  typedef bool (*DataWidgetFunction)(rttr::variant& object, rttr::string_view name);
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
      static bool UseWidget(rttr::variant& object, rttr::string_view name = rttr::string_view(), bool treeNode = false);

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

      static bool FloatWidget(rttr::variant& object, rttr::string_view name);

      static bool DoubleWidget(rttr::variant& object, rttr::string_view name);

      static bool IntWidget(rttr::variant& object, rttr::string_view name);

      static bool UnsignedIntWidget(rttr::variant& object, rttr::string_view name);

      static bool CharWidget(rttr::variant& object, rttr::string_view name);

      static bool UnsignedCharWidget(rttr::variant& object, rttr::string_view name);

      static bool ShortWidget(rttr::variant& object, rttr::string_view name);

      static bool UnsignedShortWidget(rttr::variant& object, rttr::string_view name);

      static bool LongLongWidget(rttr::variant& object, rttr::string_view name);

      static bool UnsignedLongLongWidget(rttr::variant& object, rttr::string_view name);

      static bool StringWidget(rttr::variant& object, rttr::string_view name);

      static bool RotationWidget(rttr::variant& object, rttr::string_view name);

    private:
      static DataWidgetFunctionMap widgetFunctions_;
      static bool initialized_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DataWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////