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

#include "Objects/Components/BaseClasses/Component.hpp"
#include "Objects/Components/BaseClasses/ComponentArray.hpp"
#include "Objects/Pools/Pool.hpp"

#include <vector>
#include <unordered_map>
#include <string>

namespace Barrage
{
  class ComponentAllocator;
  
  typedef Component* (*ComponentAllocFunc)(Component*);
  typedef ComponentArray* (*ComponentArrayAllocFunc)(unsigned);

  typedef std::unordered_map<std::string_view, ComponentAllocFunc> ComponentAllocUmap;
  typedef std::unordered_map<std::string_view, ComponentArrayAllocFunc> ComponentArrayAllocUmap;

  //! Responsible for allocating new components
  class ComponentAllocator
	{
    public:   
      ComponentAllocator() = delete;

      /**************************************************************/
      /*!
        \brief
          Tells the allocator how to allocate a component for
          a given type.

        \tparam T
          The type of data the component will wrap.

        \param componentName
          The name of the component's C++ class.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterComponent(const std::string_view& componentName);

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
          Tells the allocator that a given tag exists in the engine.

        \param tag
          The tag to register.
      */
      /**************************************************************/
      static void RegisterTag(const std::string_view& tag);

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
      static Component* AllocateComponent(const std::string_view& name, Component* initializer = nullptr);

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
          Gets the string literal name of a component (wrapped
          in a string_view) if it has been registered.

        \param component
          The component to get the name of.

        \return
          Returns the string literal name of a component
          (wrapped in a string_view) if it has been registered,
          returns an empty string_view otherwise.
      */
      /**************************************************************/
      static std::string_view GetComponentLiteral(const std::string_view& component);

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
          Gets the list of all registered components.

        \return
          Returns the list of all registered components.
      */
      /**************************************************************/
      static const std::vector<std::string_view>& GetComponentNames();

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
          Gets the list of all registered tags.

        \return
          Returns the list of all registered tags.
      */
      /**************************************************************/
      static const std::vector<std::string_view>& GetTagNames();

    private:
      /**************************************************************/
      /*!
        \brief
          Creates a component of the input type.

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
      static Component* AllocateComponent(Component* initializer);
      
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

    private:
      static ComponentAllocUmap componentAllocMap_;           //!< Maps names of shared components to their allocation functions
      static ComponentArrayAllocUmap componentArrayAllocMap_; //!< Maps names of component arrays to their allocation functions
      static TagSet tagSet_;                                 //!< Set of all tags registered with the engine

      static std::vector<std::string_view> componentNames_;   //!< The names of all registered shared components
      static std::vector<std::string_view> componentArrayNames_;    //!< The names of all registered component arrays
      static std::vector<std::string_view> tagNames_;

      static bool componentNamesSorted_; 
      static bool componentArrayNamesSorted_;
      static bool tagNamesSorted_;
	};
}

#include "ComponentAllocator.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////