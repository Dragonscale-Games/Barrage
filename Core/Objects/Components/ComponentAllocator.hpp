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

  typedef std::unordered_map<std::string_view, ComponentArrayAllocFunc> ComponentArrayAllocMap;
  typedef std::unordered_map<std::string_view, SharedComponentAllocFunc> SharedComponentAllocMap;

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
      void RegisterComponent(const std::string_view& componentName);

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
      ComponentArray* AllocateComponentArray(const std::string_view& name, unsigned capacity) const;

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
      SharedComponent* AllocateSharedComponent(const std::string_view& name, SharedComponent* initializer = nullptr) const;

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered component arrays.

        \return
          Returns the list of all registered component arrays.
      */
      /**************************************************************/
      static const std::vector<std::string_view>& GetComponentArrayNames();
      
      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered shared components.

        \return
          Returns the list of all registered shared components.
      */
      /**************************************************************/
      static const std::vector<std::string_view>& GetSharedComponentNames();

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
      static ComponentArrayAllocMap componentArrayAllocMap_;   //!< Maps names of component arrays to their allocation functions
      static SharedComponentAllocMap sharedComponentAllocMap_; //!< Maps names of shared components to their allocation functions

      static std::vector<std::string_view> componentArrayNames_;    //!< The names of all registered component arrays
      static std::vector<std::string_view> sharedComponentNames_;   //!< The names of all registered shared components

      static bool componentArrayNamesSorted_;
      static bool sharedComponentNamesSorted_; 
	};
}

#include "ComponentAllocator.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////