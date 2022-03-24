/* ======================================================================== */
/*!
 * \file            ComponentAllocator.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentAllocator_BARRAGE_H
#define ComponentAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "EngineComponents.hpp"

#include <vector>

namespace Barrage
{
  class ComponentAllocator;
  
  typedef ObjectComponent* (ComponentAllocator::* ObjectComponentAllocFunc)(unsigned) const;
  typedef PoolComponent* (ComponentAllocator::* PoolComponentAllocFunc)(PoolComponent*) const;

  typedef std::unordered_map<std::string, ObjectComponentAllocFunc> ObjectComponentAllocMap;
  typedef std::unordered_map<std::string, PoolComponentAllocFunc> PoolComponentAllocMap;

  //! <class description>
  class ComponentAllocator
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      ComponentAllocator();

      /**************************************************************/
      /*!
        \brief
          Tells the component allocator how to allocate a component
          of a given type. Specializes one of the templated allocation 
          functions below and adds it to the corresponding allocation 
          function map.

        \tparam T
          The type of the component to register.

        \param componentName
          The name the user would like to be assigned to the component.
      */
      /**************************************************************/
      template <typename T>
      void RegisterComponent(const std::string& componentName);

      /**************************************************************/
      /*!
        \brief
          Creates an array of the object component type with the input
          name with a number of elements equal to the input capacity.
          If no component with that name has been registered, returns
          nullptr.

        \param name
          The name of the object component to allocate.

        \param capacity
          The number of object components the allocated array should
          hold.

        \return
          Returns a pointer to the newly allocated array if the
          component type has been registered, otherwise returns
          nullptr.
      */
      /**************************************************************/
      ObjectComponent* AllocateObjectComponentArray(const std::string& name, unsigned capacity) const;

      /**************************************************************/
      /*!
        \brief
          Creates a pool component of the input type. If no component 
          with that name has been registered, returns nullptr.

        \param name
          The name of the pool component to allocate.

        \param other
          Optional initializer component. If nullptr, allocated pool
          component is uninitialized.

        \return
          Returns a pointer to the newly allocated component if the
          component type has been registered, otherwise returns
          nullptr.
      */
      /**************************************************************/
      PoolComponent* AllocatePoolComponent(const std::string& name, PoolComponent* initializer = nullptr) const;

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered object components.

        \return
          Returns the list of all registered object components.
      */
      /**************************************************************/
      ObjectComponentList GetObjectComponentNames();
      
      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered pool components.

        \return
          Returns the list of all registered pool components.
      */
      /**************************************************************/
      PoolComponentList GetPoolComponentNames();

    private:
      /**************************************************************/
      /*!
        \brief
          A generic object component allocation function that creates
          an array of the input object component type with a number
          of elements equal to the input capacity.

        \tparam T
          The type of the object component to allocate.

        \param capacity
          The number of object components the allocated array should
          hold.

        \return
          Returns a pointer to the newly allocated array.
      */
      /**************************************************************/
      template <typename T>
      ObjectComponent* AllocateObjectComponentArray(unsigned capacity) const;

      /**************************************************************/
      /*!
        \brief
          A generic pool component allocation function that creates a
          pool component of the input type.

        \tparam T
          The type of the pool component to allocate.

        \param initializer
          Optional initializer component. If nullptr, allocated
          component is uninitialized.

        \return
          Returns a pointer to the newly allocated component.
      */
      /**************************************************************/
      template <typename T>
      PoolComponent* AllocatePoolComponent(PoolComponent* initializer) const;

    private:
      ObjectComponentAllocMap objectComponentAllocMap_; //!< Maps names of object components to their allocation functions
      PoolComponentAllocMap poolComponentAllocMap_;     //!< Maps names of pool components to their allocation functions

      ObjectComponentList objectComponentNames_;        //!< The names of all registered object components
      PoolComponentList poolComponentNames_;            //!< The names of all registered pool components
	};
}

#include "ComponentAllocator.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////