/* ======================================================================== */
/*!
 * \file            ComponentAllocator.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of component via its name.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentAllocator_BARRAGE_T
#define ComponentAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  template <typename T>
  void ComponentFactory::RegisterComponent(const std::string& componentName)
  {
    if (componentNames_.count(componentName))
    {
      return;
    }

    componentNames_.insert(componentName);
    componentFactoryMethodMap_[componentName] = &ComponentFactory::AllocateComponent<T>;
  }

  template <typename T>
  void ComponentFactory::RegisterComponentArray(const std::string& componentName)
  {
    if (componentArrayNames_.count(componentName))
    {
      return;
    }

    componentArrayNames_.insert(componentName);
    componentArrayFactoryMethodMap_[componentName] = &ComponentFactory::AllocateComponentArray<T>;
  }

  template <typename T>
  std::shared_ptr<Component> ComponentFactory::AllocateComponent(std::shared_ptr<Component> initializer)
  {
    std::shared_ptr<ComponentT<T>> new_component = std::make_shared<ComponentT<T>>();
    std::shared_ptr<ComponentT<T>> initializer_full = std::dynamic_pointer_cast<ComponentT<T>>(initializer);

    if (initializer_full)
    {
      new_component->Data() = initializer_full->Data();
    }

    return new_component;
  }

  template <typename T>
  std::shared_ptr<ComponentArray> ComponentFactory::AllocateComponentArray(unsigned capacity)
  {
    return std::make_shared<ComponentArrayT<T>>(capacity);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////