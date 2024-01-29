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

#include "ComponentArray.hpp"

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
          Sets the maximum number of objects for any per-object data
          on the component.

        \param capacity
          The new capacity to set.
      */
      /**************************************************************/
      virtual void SetCapacity(unsigned capacity) = 0;

      /**************************************************************/
      /*!
        \brief
          Handles destructions for any per-object data in the 
          component.

        \param destructionArray
          Array of bools denoting whether an object at a given index
          is destroyed (true) or alive (false).

        \param writeIndex
          The index of the first dead object.

        \param endIndex
          One past the index of the last object that could be alive.

        \return
          Returns the number of alive objects.
      */
      /**************************************************************/
      virtual void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) = 0;

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
          Sets the maximum number of objects for any per-object data
          on the component. Default implementation does nothing; this
          should be specialized if the component has any per-object
          data.

        \param capacity
          The new capacity to set.
      */
      /**************************************************************/
      void SetCapacity(unsigned capacity) override;

      /**************************************************************/
      /*!
        \brief
          Handles destructions for any per-object data in the
          component. Default implementation does nothing; must be
          specialized if component has per-object data.

        \param destructionArray
          Array of bools denoting whether an object at a given index
          is destroyed (true) or alive (false).

        \param writeIndex
          The index of the first dead object.

        \param endIndex
          One past the index of the last object that could be alive.

        \return
          Returns the number of alive objects.
      */
      /**************************************************************/
      void HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) override;

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

  using ComponentMap = std::map<std::string, DeepPtr<Component>>;
}

#include "Component.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Component_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////