/* ======================================================================== */
/*!
 * \file            DeepPtr.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Generic pointer class that makes a deep copy of the object it points to 
   when copied.

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeepPtr_BARRAGE_H
#define DeepPtr_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <memory>

namespace Barrage
{
  template <typename T>
  class DeepPtr
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default/conversion constructor. Wraps a nullptr.

        \param nullPointer
          Dummy parameter. Allows default parameter conversion like:
            Foo(DeepPtr<Bar> pointer = nullptr)
      */
      /**************************************************************/
      DeepPtr(std::nullptr_t nullPointer = nullptr);

      /**************************************************************/
      /*!
        \brief
          Constructs the DeepPtr from a shared pointer. The
          shared pointer is stored internally (wrapped).

        \param ptr
          The shared pointer to wrap.
      */
      /**************************************************************/
      DeepPtr(std::shared_ptr<T> ptr);

      /**************************************************************/
      /*!
        \brief
          Copy constructor which deep copies the pointed-to object.

        \param other
          The pointer to an object to deep copy.
      */
      /**************************************************************/
      DeepPtr(const DeepPtr& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator for deep copying a component
          pointer.

        \param other
          The component pointer to deep copy.
      */
      /**************************************************************/
      DeepPtr& operator=(const DeepPtr& other);

      /**************************************************************/
      /*!
        \brief
          Move constructor. Transfers ownership of the managed
          object from the source component pointer.

        \param other
          The component pointer to move.
      */
      /**************************************************************/
      DeepPtr(DeepPtr&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Move assignment operator. Transfers ownership of the
          managed object from the source component pointer.

        \param other
          The component pointer to move.
      */
      /**************************************************************/
      DeepPtr& operator=(DeepPtr&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Arrow operator overload.

        \return
          Returns the underlying object as a pointer.
      */
      /**************************************************************/
      T* operator->() const;

      /**************************************************************/
      /*!
        \brief
          Star operator overload.

        \return
          Returns the underlying object as a reference.
      */
      /**************************************************************/
      T& operator*() const;

      /**************************************************************/
      /*!
        \brief
          Bool conversion operator. Allows easy nullptr checks.
      */
      /**************************************************************/
      operator bool() const noexcept;

      /**************************************************************/
      /*!
        \brief
          Gets the raw pointer that's wrapped.
      */
      /**************************************************************/
      std::shared_ptr<T> Get();

    private:
      std::shared_ptr<T> ptr_;
  };
}

#include "DeepPtr.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // DeepPtr_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////