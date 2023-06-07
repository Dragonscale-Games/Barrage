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

#include <rttr/rttr_enable.h>

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
      virtual rttr::variant GetRTTRValue() = 0;

      /**************************************************************/
      /*!
        \brief
          Sets the component value using an rttr::variant. When
          possible, use Data() function to access component instead.
      */
      /**************************************************************/
      virtual void SetRTTRValue(const rttr::variant& value) = 0;

      // Notify rttr of the component hierarchy.
      RTTR_ENABLE()
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
      rttr::variant GetRTTRValue() override;

      /**************************************************************/
      /*!
        \brief
          Sets the component value using an rttr::variant. When
          possible, use Data() function to access component instead.
      */
      /**************************************************************/
      void SetRTTRValue(const rttr::variant& value) override;

    public:
      T data_;

      RTTR_ENABLE(Component)
  };

  //! Associates each shared component with its name
  typedef std::unordered_map<std::string_view, Component*> ComponentMap;
}

#include "Component.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Component_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////