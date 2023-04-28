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

#include <stdexcept>

namespace Barrage
{
  template <typename T>
  T DataWidget::DataObject::GetValue()
  {
    if (!value_.is_type<T>())
    {
      throw std::runtime_error("RTTR variant did not match input type in DataObject::GetValue()");
    }
    
    return value_.get_value<T>();
  }

  template <typename T>
  void DataWidget::DataObject::SetValue(const T& newValue)
  {
    if (!value_.is_type<T>())
    {
      throw std::runtime_error("RTTR variant did not match input type in DataObject::SetValue()");
    }

    value_ = newValue;
    valueWasSet_ = true;
  }
  
  template <typename T>
  void DataWidget::Use(T& object, const std::string& name, bool treeNode)
  {
    rttr::variant objectPointer = &object;
    DataObject dataObject(name, objectPointer);
    DataWidget::Use(dataObject, treeNode);
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