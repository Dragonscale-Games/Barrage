/* ======================================================================== */
/*!
 * \file            ComponentArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component array class that all component arrays should inherit from.
   Component arrays are used when each object in a pool needs its own copy
   of a component.
   For instance, each object may need its own position component.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentArray_BARRAGE_H
#define ComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseComponent.hpp"
#include <vector>
#include <rttr/rttr_enable.h>

namespace Barrage
{ 
  //! Base component array class that all component arrays inherit from
  class ComponentArray : public Component
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~ComponentArray() = default;

      /**************************************************************/
      /*!
        \brief
          Allocates the component array for a given component type.

        \param capacity
          The number of elements in the component array.
      */
      /**************************************************************/
      virtual void Allocate(unsigned capacity) = 0;

      /**************************************************************/
      /*!
        \brief
          Copies a component from some source component array to a 
          recipient component in this component array.

        \param source
          The component array holding the component to copy from. The
          source may be this component array.

        \param sourceIndex
          The index of the component to copy from.

        \param recipientIndex
          The index of the component in this component array to copy
          to.
      */
      /**************************************************************/
      virtual void CopyToThis(const ComponentArray& source, unsigned sourceIndex, unsigned recipientIndex) = 0;

      /**************************************************************/
      /*!
        \brief
          Used to identify this object as a component array.

        \return
          Returns the "ARRAY" component type.
      */
      /**************************************************************/
      virtual Component::Type GetType() override;

      /**************************************************************/
      /*!
        \brief
          Gets the value at index i of the array as an rttr::variant.

          For non-RTTR value getting, use operator[].

        \param i
          The index of the value to get.

        \return
          Returns the value at the given index as an rttr::variant.
      */
      /**************************************************************/
      virtual rttr::variant GetRTTRValue(int i) = 0;

      /**************************************************************/
      /*!
        \brief
          Sets the value at index i using an rttr::variant. If the
          rttr::variant doesn't match type T, this function has no
          effect.

          For non-RTTR value setting, use operator[].

        \param i
          The index of the value to set.

        \return
          Returns the value at the given index as an rttr::variant.
      */
      /**************************************************************/
      virtual void SetRTTRValue(int i, rttr::variant& value) = 0;

      RTTR_ENABLE(Component)
  };

  //! All component arrays are a specialization of this template
  template <typename T>
  class ComponentArrayT : public ComponentArray
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes with a null component array.
      */
      /**************************************************************/
      ComponentArrayT();

      /**************************************************************/
      /*!
        \brief
          Deallocates component array.
      */
      /**************************************************************/
      virtual ~ComponentArrayT();

      /**************************************************************/
      /*!
        \brief
          Allocates component array with the given number of elements.

        \param capacity
          The number of elements in the component array.
      */
      /**************************************************************/
      void Allocate(unsigned capacity) override;

      /**************************************************************/
      /*!
        \brief
          Copies a component from some source component array to a
          recipient component in this component array.

        \param source
          The component array holding the component to copy from. The
          source may be this component array.

        \param sourceIndex
          The index of the component to copy from.

        \param recipientIndex
          The index of the component in this component array to copy
          to.
      */
      /**************************************************************/
      void CopyToThis(const ComponentArray& source, unsigned sourceIndex, unsigned recipientIndex) override;

      /**************************************************************/
      /*!
        \brief
          Accesses the component at a given index in the array.

        \param i
          The index of the component to access.

        \return
          Returns a reference to the accessed component.
      */
      /**************************************************************/
      T& operator[](int i);

      /**************************************************************/
      /*!
        \brief
          Gets the value at index i of the array as an rttr::variant.

          For non-RTTR value getting, use operator[].

        \param i
          The index of the value to get.

        \return
          Returns the value at the given index as an rttr::variant.
      */
      /**************************************************************/
      rttr::variant GetRTTRValue(int i) override;

      /**************************************************************/
      /*!
        \brief
          Sets the value at index i using an rttr::variant. If the
          rttr::variant doesn't match type T, this function has no
          effect.

          For non-RTTR value setting, use operator[].

        \param i
          The index of the value to set.

        \return
          Returns the value at the given index as an rttr::variant.
      */
      /**************************************************************/
      void SetRTTRValue(int i, rttr::variant& value) override;

    public:
      T* data_;

    RTTR_ENABLE(ComponentArray)
  };

  //! Associates each component array with its name
  typedef std::unordered_map<std::string_view, ComponentArray*> ComponentArrayMap;
}

#include "ComponentArray.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////