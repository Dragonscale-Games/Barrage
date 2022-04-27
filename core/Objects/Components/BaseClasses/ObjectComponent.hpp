/* ======================================================================== */
/*!
 * \file            ObjectComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base object component classes and template class for object components.
   All object components should be a specialization of the template class
   ObjectComponentDerived.

   An object component is a component that is unique per object that contains
   it.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectComponent_BARRAGE_H
#define ObjectComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseComponent.hpp"
#include <vector>

namespace Barrage
{ 
  //! Base object component class that all object components derive from
  class ObjectComponent : public Component
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~ObjectComponent() = default;

      /**************************************************************/
      /*!
        \brief
          Allocates the component array that a given component type
          uses.

        \param capacity
          The number of elements in the component array.
      */
      /**************************************************************/
      virtual void Allocate(unsigned capacity) = 0;

      /**************************************************************/
      /*!
        \brief
          Copies an object component from some source component array
          to a recipient in this component array.

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
      virtual void CopyToThis(const ObjectComponent& source, unsigned sourceIndex, unsigned recipientIndex) = 0;

      /**************************************************************/
      /*!
        \brief
          Tells user this is an object component type.

        \return
          Returns object component type to identify component.
      */
      /**************************************************************/
      virtual Component::Type GetType() override;
  };

  //! Template for an object component class
  template <typename T>
  class ObjectComponentDerived : public ObjectComponent
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes component with empty data array.
      */
      /**************************************************************/
      ObjectComponentDerived();
      
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~ObjectComponentDerived();

      /**************************************************************/
      /*!
        \brief
          Allocates the component array that a given component type
          uses.

        \param capacity
          The number of elements in the component array.
      */
      /**************************************************************/
      void Allocate(unsigned capacity) override;

      /**************************************************************/
      /*!
        \brief
          Copies an object component from some source component array
          to a recipient in this component array.

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
      void CopyToThis(const ObjectComponent& source, unsigned sourceIndex, unsigned recipientIndex) override;

    public:
      T* data_;
  };

  //! Maps object component names to object component arrays
  typedef std::unordered_map<std::string, ObjectComponent*> ObjectComponentMap;

  //! Contains a list of names of object components
  typedef std::vector<std::string> ObjectComponentList;
}

#include "ObjectComponent.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////