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

#include <vector>
#include <string>
#include <rttr/rttr_enable.h>
#include <rttr/variant.h>

namespace Barrage
{ 
  //! Base component array class that all component arrays inherit from
  class ComponentArray
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
          Using the destructionArray to see which objects have been
          destroyed, tightly packs the remaining alive objects at
          the beginning of the array.

        \param destructionArray
          Array of bools denoting whether an object at a given index
          is destroyed (true) or alive (false).

        \param deadBeginIndex
          Optimization hint that holds the index of the first dead
          object in the array.

        \param aliveEndIndex
          Optimization hint that holds one past the index of the
          last object that could be alive.

        \return
          Returns the number of alive objects.
      */
      /**************************************************************/
      virtual unsigned HandleDestructions(const bool* destructionArray, unsigned deadBeginIndex, unsigned aliveEndIndex) = 0;

      /**************************************************************/
      /*!
        \brief
          Gets an rttr::variant representation of the component at
          some index. Should not generally be used except for
          serialization/the editor.

        \param index
          The index of the component to get.

        \return
          Returns the value of the component as an rttr::variant.
      */
      /**************************************************************/
      virtual rttr::variant GetRTTRValue(int index) = 0;

      /**************************************************************/
      /*!
        \brief
          Sets the component value at some index using an rttr::variant.
          Should not generally be used except for serialization or
          the editor.
      */
      /**************************************************************/
      virtual void SetRTTRValue(const rttr::variant& value, int index) = 0;

      RTTR_ENABLE()
  };

  //! All component arrays are a specialization of this template
  template <typename T>
  class ComponentArrayT : public ComponentArray
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs a component array with the given capacity.

        \param capacity
          The number of components held in the array.
      */
      /**************************************************************/
      ComponentArrayT(unsigned capacity = 1);

      /**************************************************************/
      /*!
        \brief
          Copy constructor.

        \param other
          The array to copy.
      */
      /**************************************************************/
      ComponentArrayT(const ComponentArrayT<T>& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator.

        \param other
          The array to copy.
      */
      /**************************************************************/
      ComponentArrayT<T>& operator=(const ComponentArrayT<T>& other);

      /**************************************************************/
      /*!
        \brief
          Deallocates component array.
      */
      /**************************************************************/
      ~ComponentArrayT() override;

      /**************************************************************/
      /*!
        \brief
          Reallocates the data array with a new capacity.
          Note: Sets all values to default values.

        \param capacity
          The new capacity to set.
      */
      /**************************************************************/
      void SetCapacity(unsigned capacity);

      /**************************************************************/
      /*!
        \brief
          Copies a component from some source component array to a
          recipient component in this component array. The arrays
          should be the same type (this function is not safety
          checked).

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
          Using the destructionArray to see which objects have been
          destroyed, tightly packs the remaining alive objects at
          the beginning of the array.

        \param destructionArray
          Array of bools denoting whether an object at a given index
          is destroyed (true) or alive (false).

        \param deadBeginIndex
          Optimization hint that holds the index of the first dead
          object in the array.

        \param aliveEndIndex
          Optimization hint that holds one past the index of the
          last object that could be alive.
      */
      /**************************************************************/
      unsigned HandleDestructions(const bool* destructionArray, unsigned deadBeginIndex, unsigned aliveEndIndex) override;

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
      T& Data(int index);

      /**************************************************************/
      /*!
        \brief
          Gets an rttr::variant representation of the component at
          some index. Should not generally be used except for
          serialization/the editor.

        \param index
          The index of the component to get.

        \return
          Returns the value of the component as an rttr::variant.
      */
      /**************************************************************/
      rttr::variant GetRTTRValue(int index) override;

      /**************************************************************/
      /*!
        \brief
          Sets the component value at some index using an rttr::variant.
          Should not generally be used except for serialization or
          the editor.
      */
      /**************************************************************/
      void SetRTTRValue(const rttr::variant& value, int index) override;

    private:
      T* data_;
      unsigned capacity_;

    RTTR_ENABLE(ComponentArray)
  };

  //! Associates each component array with its name
  typedef std::unordered_map<std::string_view, ComponentArray*> ComponentArrayUmap;
}

#include "ComponentArray.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////