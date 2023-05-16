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
  
  typedef ComponentArray* (*ComponentArrayAllocFunc)(unsigned);
  typedef SharedComponent* (*SharedComponentAllocFunc)(SharedComponent*);

  typedef std::unordered_map<std::string_view, ComponentArrayAllocFunc> ComponentArrayAllocMap;
  typedef std::unordered_map<std::string_view, SharedComponentAllocFunc> SharedComponentAllocMap;

  //! Responsible for allocating new components
  class ComponentAllocator
	{
    public:   
      ComponentAllocator() = delete;

      /**************************************************************/
      /*!
        \brief
          Tells the allocator how to allocate a component array for 
          a given type. 

        \tparam T
          The type of component the array will contain.

        \param componentName
          The name of the component's C++ class.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterComponentArray(const std::string_view& componentName);

      /**************************************************************/
      /*!
        \brief
          Tells the allocator how to allocate a shared component for 
          a given type. 

        \tparam T
          The type of component data the shared component will wrap.

        \param componentName
          The name of the component's C++ class.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterSharedComponent(const std::string_view& componentName);

      /**************************************************************/
      /*!
        \brief
          Tells the allocator how to allocate a shared component for
          a given type.

        \tparam T
          The type of component data the shared component will wrap.

        \param componentName
          The name of the component's C++ class.
      */
      /**************************************************************/
      static void RegisterTag(const std::string_view& tag);

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
      static ComponentArray* AllocateComponentArray(const std::string_view& name, unsigned capacity);

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
      static SharedComponent* AllocateSharedComponent(const std::string_view& name, SharedComponent* initializer = nullptr);

      /**************************************************************/
      /*!
        \brief
          Gets the string literal name of a component array (wrapped 
          in a string_view) if it has been registered.

        \param componentArray
          The component array to get the name of.

        \return
          Returns the string literal name of a component array 
          (wrapped in a string_view) if it has been registered, 
          returns an empty string_view otherwise.
      */
      /**************************************************************/
      static std::string_view GetComponentArrayLiteral(const std::string_view& componentArray);

      /**************************************************************/
      /*!
        \brief
          Gets the string literal name of a shared component (wrapped
          in a string_view) if it has been registered.

        \param sharedComponent
          The shared component to get the name of.

        \return
          Returns the string literal name of a shared component
          (wrapped in a string_view) if it has been registered,
          returns an empty string_view otherwise.
      */
      /**************************************************************/
      static std::string_view GetSharedComponentLiteral(const std::string_view& sharedComponent);

      /**************************************************************/
      /*!
        \brief
          Gets the string literal name of a tag (wrapped in a
          string_view) if it has been registered.

        \param tag
          The tag to get the name of.

        \return
          Returns the string literal name of a tag (wrapped in a
          string_view) if it has been registered, returns an empty 
          string_view otherwise.
      */
      /**************************************************************/
      static std::string_view GetTagLiteral(const std::string_view& tag);

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

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered shared components.

        \return
          Returns the list of all registered shared components.
      */
      /**************************************************************/
      static const std::vector<std::string_view>& GetTagNames();

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
      static ComponentArray* AllocateComponentArray(unsigned capacity);

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
      static SharedComponent* AllocateSharedComponent(SharedComponent* initializer);

    private:
      static ComponentArrayAllocMap componentArrayAllocMap_;   //!< Maps names of component arrays to their allocation functions
      static SharedComponentAllocMap sharedComponentAllocMap_; //!< Maps names of shared components to their allocation functions
      static TagSet tagSet_;                                   //!< Set of all tags registered with the engine

      static std::vector<std::string_view> componentArrayNames_;    //!< The names of all registered component arrays
      static std::vector<std::string_view> sharedComponentNames_;   //!< The names of all registered shared components
      static std::vector<std::string_view> tagNames_;

      static bool componentArrayNamesSorted_;
      static bool sharedComponentNamesSorted_; 
      static bool tagNamesSorted_;
	};
}

#include "ComponentAllocator.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////