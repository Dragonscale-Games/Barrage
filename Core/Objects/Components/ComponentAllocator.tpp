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
  void ComponentAllocator::RegisterComponent(const std::string_view& componentName)
  {
    if (componentAllocMap_.count(componentName))
    {
      return;
    }

    componentAllocMap_[componentName] = &ComponentAllocator::AllocateComponent<T>;
    componentNames_.push_back(componentName);
    componentNamesSorted_ = false;
  }
  
  template <typename T>
  void ComponentAllocator::RegisterComponentArray(const std::string_view& componentName)
  {
    if (componentArrayAllocMap_.count(componentName))
    {
      return;
    }

    componentArrayAllocMap_[componentName] = &ComponentAllocator::AllocateComponentArray<T>;
    componentArrayNames_.push_back(componentName);
    componentArrayNamesSorted_ = false;
  }

  template <typename T>
  Component* ComponentAllocator::AllocateComponent(Component* initializer)
  {
    ComponentT<T>* new_component = new ComponentT<T>;
    ComponentT<T>* initializer_full = dynamic_cast<ComponentT<T>*>(initializer);

    if (initializer_full)
    {
      new_component->Data() = initializer_full->Data();
    }

    return new_component;
  }

  template <typename T>
  ComponentArray* ComponentAllocator::AllocateComponentArray(unsigned capacity)
  {
    ComponentArrayT<T>* new_component_array = new ComponentArrayT<T>(capacity);

    return new_component_array;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////