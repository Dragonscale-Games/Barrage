/* ======================================================================== */
/*!
 * \file            DeepPtr.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Generic pointer class that makes a deep copy of the object it points to
   when copied.

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeepPtr_BARRAGE_T
#define DeepPtr_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  DeepPtr<T>::DeepPtr(std::nullptr_t) :
    ptr_(nullptr)
  {
  }

  template <typename T>
  DeepPtr<T>::DeepPtr(std::shared_ptr<T> ptr) :
    ptr_(ptr)
  {
  }

  template <typename T>
  DeepPtr<T>::DeepPtr(const DeepPtr<T>& other) :
    ptr_(other ? other->Clone() : nullptr)
  {
  }

  template <typename T>
  DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr<T>& other)
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = other ? other->Clone() : nullptr;
    }

    return *this;
  }

  template <typename T>
  DeepPtr<T>::DeepPtr(DeepPtr<T>&& other) noexcept :
    ptr_(std::move(other.ptr_))
  {
  }

  template <typename T>
  DeepPtr<T>& DeepPtr<T>::operator=(DeepPtr<T>&& other) noexcept
  {
    if (this != &other) // Prevent self-assignment
    {
      ptr_ = std::move(other.ptr_);
    }

    return *this;
  }

  template <typename T>
  T* DeepPtr<T>::operator->() const
  {
    return ptr_.operator->();
  }

  template <typename T>
  T& DeepPtr<T>::operator*() const
  {
    return *ptr_;
  }

  template <typename T>
  DeepPtr<T>::operator bool() const noexcept
  {
    return static_cast<bool>(ptr_);
  }

  template <typename T>
  std::shared_ptr<T> DeepPtr<T>::Get()
  {
    return ptr_;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeepPtr_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////