/* ======================================================================== */
/*!
 * \file            DataWidget.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shows a widget that allows the user to edit a field on an object
   registered with RTTR.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DataWidget_BARRAGE_T
#define DataWidget_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  void DataWidget::Use(T& object, rttr::string_view name, bool treeNode)
  {
    rttr::variant objectPointer = &object;
    DataWidget::Use(objectPointer, name, treeNode);
  }
  
  template <typename T>
  void DataWidget::AddDataWidget(DataWidgetFunction widgetFunction)
  {
    rttr::type type = rttr::type::get<T>();
    
    if (!type.is_valid())
    {
      return;
    }

    std::string typeName = type.get_name().data();
    widgetFunctions_[typeName] = widgetFunction;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DataWidget_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////