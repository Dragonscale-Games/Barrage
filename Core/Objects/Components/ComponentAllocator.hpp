/* ======================================================================== */
/*!
 * \file            ComponentAllocator.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentAllocator_BARRAGE_H
#define ComponentAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "EngineComponents.hpp"

#include <vector>
#include <unordered_map>
#include <string>

namespace Barrage
{
  class ComponentAllocator;
  
  typedef ComponentArray* (ComponentAllocator::* ComponentArrayAllocFunc)(unsigned) const;
  typedef SharedComponent* (ComponentAllocator::* SharedComponentAllocFunc)(SharedComponent*) const;

  typedef std::unordered_map<std::string, ComponentArrayAllocFunc> ComponentArrayAllocMap;
  typedef std::unordered_map<std::string, SharedComponentAllocFunc> SharedComponentAllocMap;

  //! Responsible for allocating new components
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
          of a given type. Component must inherit from one of the
          component base classes.

        \tparam T
          The type of the component to register.

        \param componentName
          The name the user would like assigned to the component.
      */
      /**************************************************************/
      template <typename T>
      void RegisterComponent(const std::string& componentName);

      /**************************************************************/
      /*!
        \brief
          Creates a component array whose type matches the given name. 
          If no component array with that name has been registered, 
          returns nullptr.

        \param name
          The name of the component array to allocate (must have been
          registered previously).

        \param capacity
          The number of components the array should hold.

        \return
          Returns a pointer to the newly allocated array if the
          component array type has been registered, otherwise returns
          nullptr.
      */
      /**************************************************************/
      ComponentArray* AllocateComponentArray(const std::string& name, unsigned capacity) const;

      /**************************************************************/
      /*!
        \brief
          Creates a shared component whose type matches the given 
          name. If no component with that name has been registered, 
          returns nullptr.

        \param name
          The name of the shared component to allocate.

        \param initializer
          Optional. If this argument is provided, the new component 
          will be a clone of the initializer. If not, the new 
          component will be default-constructed.

        \return
          Returns a pointer to the newly allocated component if the
          component type has been registered, otherwise returns
          nullptr.
      */
      /**************************************************************/
      SharedComponent* AllocateSharedComponent(const std::string& name, SharedComponent* initializer = nullptr) const;

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered component arrays.

        \return
          Returns the list of all registered component arrays.
      */
      /**************************************************************/
      std::vector<std::string> GetComponentArrayNames();
      
      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered shared components.

        \return
          Returns the list of all registered shared components.
      */
      /**************************************************************/
      std::vector<std::string> GetSharedComponentNames();

    private:
      /**************************************************************/
      /*!
        \brief
          Creates a component array, where each array element is of 
          the input type.

        \tparam T
          The type of component to allocate.

        \param capacity
          The number of components the array should hold.

        \return
          Returns a pointer to the newly allocated array.
      */
      /**************************************************************/
      template <typename T>
      ComponentArray* AllocateComponentArray(unsigned capacity) const;

      /**************************************************************/
      /*!
        \brief
          Creates a shared component of the input type.

        \tparam T
          The type of component to allocate.

        \param initializer
          If this argument is non-null, the new component will be a 
          clone of the initializer. Otherwise, the component will be
          default-constructed.

        \return
          Returns a pointer to the newly allocated component.
      */
      /**************************************************************/
      template <typename T>
      SharedComponent* AllocateSharedComponent(SharedComponent* initializer) const;

    private:
      ComponentArrayAllocMap componentArrayAllocMap_;   //!< Maps names of component arrays to their allocation functions
      SharedComponentAllocMap sharedComponentAllocMap_; //!< Maps names of shared components to their allocation functions

      std::vector<std::string> componentArrayNames_;    //!< The names of all registered component arrays
      std::vector<std::string> sharedComponentNames_;   //!< The names of all registered shared components
	};
}

#include "ComponentAllocator.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////