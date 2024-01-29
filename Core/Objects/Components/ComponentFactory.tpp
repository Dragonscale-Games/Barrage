/* ======================================================================== */
/*!
 * \file            ComponentFactory.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentFactory_BARRAGE_T
#define ComponentFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  void ComponentFactory::RegisterComponent(const std::string& componentName)
  {
    if (componentFactoryMethodMap_.count(componentName))
    {
      return;
    }

    componentNames_.insert(componentName);
    componentFactoryMethodMap_[componentName] = &ComponentFactory::AllocateComponent<T>;
  }

  template <typename T>
  void ComponentFactory::RegisterComponentArray(const std::string& componentName)
  {
    if (componentArrayFactoryMethodMap_.count(componentName))
    {
      return;
    }

    componentArrayNames_.insert(componentName);
    componentArrayFactoryMethodMap_[componentName] = &ComponentFactory::AllocateComponentArray<T>;
  }

  template <typename T>
  DeepPtr<Component> ComponentFactory::AllocateComponent(DeepPtr<Component> initializer)
  {
    if (initializer)
    {
      return initializer->Clone();
    }
    else
    {
      return std::make_shared<ComponentT<T>>();
    }
  }

  template <typename T>
  DeepPtr<ComponentArray> ComponentFactory::AllocateComponentArray(unsigned capacity)
  {
    return DeepPtr<ComponentArray>(std::make_shared<ComponentArrayT<T>>(capacity));
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////