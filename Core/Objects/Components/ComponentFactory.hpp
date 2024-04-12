/* ======================================================================== */
/*!
 * \file            ComponentFactory.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentFactory_BARRAGE_H
#define ComponentFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/Component.hpp"
#include "Objects/Components/ComponentArray.hpp"
#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  class ComponentFactory;

  using ComponentFactoryMethod = DeepPtr<Component>(*)(DeepPtr<Component>);
  using ComponentArrayFactoryMethod = DeepPtr<ComponentArray>(*)(unsigned);

  using ComponentFactoryMethodMap = std::map<std::string, ComponentFactoryMethod>;
  using ComponentArrayFactoryMethodMap = std::map<std::string, ComponentArrayFactoryMethod>;

  //! Responsible for allocating new components
  class ComponentFactory
  {
    public:
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
      static void RegisterComponent(const std::string& componentName);

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
      static void RegisterComponentArray(const std::string& componentName);

      /**************************************************************/
      /*!
        \brief
          Tells the allocator that a given tag exists in the engine.

        \param tag
          The tag to register.
      */
      /**************************************************************/
      static void RegisterTag(const std::string& tag);

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
      static DeepPtr<Component> AllocateComponent(const std::string& name, DeepPtr<Component> initializer = nullptr);

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
      static DeepPtr<ComponentArray> AllocateComponentArray(const std::string& name, unsigned capacity);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered components.

        \return
          Returns the list of all registered components.
      */
      /**************************************************************/
      static const StringSet& GetComponentNames();

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered component arrays.

        \return
          Returns the list of all registered component arrays.
      */
      /**************************************************************/
      static const StringSet& GetComponentArrayNames();

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered tags.

        \return
          Returns the list of all registered tags.
      */
      /**************************************************************/
      static const StringSet& GetTagNames();

    private:
      ComponentFactory() = delete;
      ComponentFactory(const ComponentFactory&) = delete;
      ComponentFactory& operator=(const ComponentFactory&) = delete;
      ~ComponentFactory() = delete;

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
      static DeepPtr<Component> AllocateComponent(DeepPtr<Component> initializer);

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
      static DeepPtr<ComponentArray> AllocateComponentArray(unsigned capacity);

    private:
      static ComponentFactoryMethodMap componentFactoryMethodMap_;           //!< Maps names of shared components to their allocation functions
      static ComponentArrayFactoryMethodMap componentArrayFactoryMethodMap_; //!< Maps names of component arrays to their allocation functions

      static StringSet componentNames_;      //!< Names of all components registered with the engine
      static StringSet componentArrayNames_; //!< Names of all component arrays registered with the engine
      static StringSet tagNames_;            //!< Names of all tags registered with the engine
  };
}

#include "ComponentFactory.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////