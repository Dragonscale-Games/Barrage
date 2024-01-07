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

#include <string>
#include <memory>
#include <map>
#include <rttr/variant.h>

namespace Barrage
{
  //!< Keeps track of whether an object is marked for destruction
  struct Destructible
  {
    bool destroyed_; //!< true if marked for destruction

    inline Destructible() : destroyed_(false) {}
  };
  
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
          Creates a component that's a deep copy of this component.

        \return
          Returns a pointer to the new component.
      */
      /**************************************************************/
      virtual std::shared_ptr<ComponentArray> Clone() const = 0;

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

        \param writeIndex
          The index of the first dead object.

        \param endIndex
          One past the index of the last object that could be alive.

        \return
          Returns the number of alive objects.
      */
      /**************************************************************/
      virtual unsigned HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) = 0;

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
      virtual rttr::variant GetRTTRValue(int index) const = 0;

      /**************************************************************/
      /*!
        \brief
          Sets the component value at some index using an rttr::variant.
          Should not generally be used except for serialization or
          the editor.
      */
      /**************************************************************/
      virtual void SetRTTRValue(const rttr::variant& value, int index) = 0;
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
          Creates a component that's a deep copy of this component.

        \return
          Returns a pointer to the new component.
      */
      /**************************************************************/
      std::shared_ptr<ComponentArray> Clone() const override;

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

        \param writeIndex
          The index of the first dead object.

        \param endIndex
          One past the index of the last object that could be alive.

        \return
          Returns the number of alive objects.
      */
      /**************************************************************/
      unsigned HandleDestructions(const Destructible* destructionArray, unsigned writeIndex, unsigned endIndex) override;

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
      rttr::variant GetRTTRValue(int index) const override;

      /**************************************************************/
      /*!
        \brief
          Sets the component value at some index using an rttr::variant.
          Should not generally be used except for serialization or
          the editor.
      */
      /**************************************************************/
      void SetRTTRValue(const rttr::variant& value, int index) override;

      /**************************************************************/
      /*!
        \brief
          Gets the raw array that this type wraps.

        \return
          Returns a pointer to this type's raw array.
      */
      /**************************************************************/
      T* GetRaw();

    private:
      T* data_;
      unsigned capacity_;
  };

  class GenericComponentArray
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default/conversion constructor. Wraps a nullptr.

        \param nullPointer
          Dummy parameter. Allows default parameter conversion like:
            Foo(GenericComponentArray pointer = nullptr)
      */
      /**************************************************************/
      GenericComponentArray(std::nullptr_t nullPointer = nullptr);
      
      /**************************************************************/
      /*!
        \brief
          Constructs this GenericComponentArray from a shared pointer. 
          The shared pointer is stored internally (wrapped).

        \param ptr
          The shared pointer to wrap.
      */
      /**************************************************************/
      GenericComponentArray(std::shared_ptr<ComponentArray> ptr);

      /**************************************************************/
      /*!
        \brief
          Copy constructor for deep copying a component array
          pointer.

        \param other
          The generic component array to deep copy.
      */
      /**************************************************************/
      GenericComponentArray(const GenericComponentArray& other);

      /**************************************************************/
      /*!
        \brief
          Copy assignment operator for deep copying a component
          array pointer.

        \param other
          The component array pointer to deep copy.
      */
      /**************************************************************/
      GenericComponentArray& operator=(const GenericComponentArray& other);

      /**************************************************************/
      /*!
        \brief
          Move constructor. Transfers ownership of the managed
          object from the source component array pointer.

        \param other
          The component array pointer to move.
      */
      /**************************************************************/
      GenericComponentArray(GenericComponentArray&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Move assignment operator. Transfers ownership of the
          managed object from the source component array pointer.

        \param other
          The component array pointer to move.
      */
      /**************************************************************/
      GenericComponentArray& operator=(GenericComponentArray&& other) noexcept;

      /**************************************************************/
      /*!
        \brief
          Arrow operator overload.

        \return
          Returns the underlying component array as a pointer.
      */
      /**************************************************************/
      ComponentArray* operator->() const;

      /**************************************************************/
      /*!
        \brief
          Star operator overload.

        \return
          Returns the underlying component array as a reference.
      */
      /**************************************************************/
      ComponentArray& operator*() const;

      /**************************************************************/
      /*!
        \brief
          Bool conversion operator. Allows easy nullptr checks.
      */
      /**************************************************************/
      operator bool() const noexcept;

    private:
      std::shared_ptr<ComponentArray> ptr_;
  };

  using ComponentArrayMap = std::map<std::string, GenericComponentArray>;
}

#include "ComponentArray.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////