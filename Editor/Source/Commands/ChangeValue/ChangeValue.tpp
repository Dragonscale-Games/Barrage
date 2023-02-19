/* ======================================================================== */
/*!
 * \file            ChangeValue.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Generic command for changing a value.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ChangeValue_BARRAGE_T
#define ChangeValue_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  ChangeValue::WriterT<T>::WriterT(DataWrapper value, const T& oldValue, const T& newValue) :
    Writer(value),
    oldValue_(oldValue),
    newValue_(newValue)
  {
  }

  template <typename T>
  void ChangeValue::WriterT<T>::WriteOldValue()
  {
    value_.SetValue<T>(oldValue_);
  }

  template <typename T>
  void ChangeValue::WriterT<T>::WriteNewValue()
  {
    value_.SetValue<T>(newValue_);
  }
  
  template <typename T>
  T ChangeValue::GetValue()
  {
    return value_.GetValue<T>();
  }

  template <typename T>
  void ChangeValue::SetValue(const T& newValue)
  {
    if (writer_)
    {
      delete writer_;
    }

    writer_ = new WriterT<T>(value_, value_.GetValue<T>(), newValue);
  }

}
////////////////////////////////////////////////////////////////////////////////
#endif // ChangeValue_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////