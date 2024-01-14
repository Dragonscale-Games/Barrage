/* ======================================================================== */
/*!
 * \file            Component.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component class that all components should inherit from.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Component_BARRAGE_H
#define Component_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <memory>
#include <map>
#include <unordered_map>
#include <rttr/variant.h>
#include <rttr/registration.h>

namespace Barrage
{
  //! Base  component class that all components should inherit from
  class Component
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~Component() = default;

      /**************************************************************/
      /*!
        \brief
          Creates a component that's a deep copy of this component.

        \return
          Returns a pointer to the new component.
      */
      /**************************************************************/
      virtual std::shared_ptr<Component> Clone() const = 0;

      /**************************************************************/
      /*!
        \brief
          Copies another component to this component. They must be
          the same type.

        \param other
          The component to copy.
      */
      /**************************************************************/
      virtual void CopyToThis(const Component& other) = 0;

      /**************************************************************/
      /*!
        \brief
          Gets an rttr::variant representation of the component. When
          possible, use Data() function to access component instead.

        \return
          Returns the component's value as an rttr::variant.
      */
      /**************************************************************/
      virtual rttr::variant GetRTTRValue() const = 0;

      /**************************************************************/
      /*!
        \brief
          Sets the component value using an rttr::variant. When
          possible, use Data() function to access component instead.
      */
      /**************************************************************/
      virtual void SetRTTRValue(const rttr::variant& value) = 0;
  };

  //! All components are a specialization of this template
  template <typename T>
  class ComponentT : public Component
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs component.
      */
      /**************************************************************/
      ComponentT();

      /**************************************************************/
      /*!
        \brief
          Creates a component that's a deep copy of this component.

        \return
          Returns a pointer to the new component.
      */
      /**************************************************************/
      std::shared_ptr<Component> Clone() const override;

      /**************************************************************/
      /*!
        \brief
          Copies another component to this component. They must be
          the same type.

        \param other
          The component to copy.
      */
      /**************************************************************/
      void CopyToThis(const Component& other) override;

      /**************************************************************/
      /*!
        \brief
          Accesses the underlying component data.

        \return
          Returns a reference to the component data.
      */
      /**************************************************************/
      T& Data();

      /**************************************************************/
      /*!
        \brief
          Gets an rttr::variant representation of the component.
          When possible, use Data() function to access component
          instead.

        \return
          Returns the component's value as an rttr::variant.
      */
      /**************************************************************/
      rttr::variant GetRTTRValue() const override;

      /**************************************************************/
      /*!
        \brief
          Sets the component value using an rttr::variant. When
          possible, use Data() function to access component instead.
      */
      /**************************************************************/
      void SetRTTRValue(const rttr::variant& value) override;

    private:
      T data_;
  };

  class ComponentDeepPtr
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default/conversion constructor. Wraps a nullptr.

        \param nullPointer
          Dummy parameter. Allows default parameter conversion like:
            Foo(ComponentDeepPtr pointer = nullptr)
      */
      /**************************************************************/
      ComponentDeepPtr(std::nullptr_t nullPointer = nullptr);
      
      /**************************************************************/
      /*!
        \brief
          Constructs this ComponentDeepPtr from a shared pointer. The
          shared pointer is stored internally (wrapped).

        \param ptr
          The shared pointer to wrap.
      */
      /**************************************************************/
      ComponentDeepPtr(std::shared_ptr<Component> ptr);

      /**************************************************************/
      /*!
        \brief
          Copy constructor for deep copying a component pointer.

        \param other
          The component pointer to deep copy.
      */
      /**************************************************************/
      ComponentDeepPtr(const ComponentDeepPtr& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator for deep copying a component
          pointer.

        \param other
          The component pointer to deep copy.
      */
      /**************************************************************/
      ComponentDeepPtr& operator=(const ComponentDeepPtr& other);

      /**************************************************************/
      /*!
        \brief
          Move constructor. Transfers ownership of the managed
          object from the source component pointer.

        \param other
          The component pointer to move.
      */
      /**************************************************************/
      ComponentDeepPtr(ComponentDeepPtr&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Move assignment operator. Transfers ownership of the
          managed object from the source component pointer.

        \param other
          The component pointer to move.
      */
      /**************************************************************/
      ComponentDeepPtr& operator=(ComponentDeepPtr&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Arrow operator overload.

        \return
          Returns the underlying component as a pointer.
      */
      /**************************************************************/
      Component* operator->() const;

      /**************************************************************/
      /*!
        \brief
          Star operator overload.

        \return
          Returns the underlying component as a reference.
      */
      /**************************************************************/
      Component& operator*() const;

      /**************************************************************/
      /*!
        \brief
          Bool conversion operator. Allows easy nullptr checks.
      */
      /**************************************************************/
      operator bool() const noexcept;

    private:
      std::shared_ptr<Component> ptr_;
  };

  using ComponentMap = std::map<std::string, ComponentDeepPtr>;
}

#include "Component.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Component_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////