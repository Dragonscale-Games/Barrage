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
  void ComponentAllocator::RegisterSharedComponent(const std::string_view& componentName)
  {
    if (sharedComponentAllocMap_.count(componentName))
    {
      return;
    }

    sharedComponentAllocMap_[componentName] = &ComponentAllocator::AllocateSharedComponent<T>;
    sharedComponentNames_.push_back(componentName);
    sharedComponentNamesSorted_ = false;
  }

  template <typename T>
  ComponentArray* ComponentAllocator::AllocateComponentArray(unsigned capacity)
  {
    ComponentArrayT<T>* new_component_array = new ComponentArrayT<T>;

    new_component_array->Allocate(capacity);

    return new_component_array;
  }

  template <typename T>
  SharedComponent* ComponentAllocator::AllocateSharedComponent(SharedComponent* initializer)
  {
    SharedComponentT<T>* new_component = new SharedComponentT<T>;
    SharedComponentT<T>* initializer_full = dynamic_cast<SharedComponentT<T>*>(initializer);

    if (initializer_full)
    {
      new_component->Data() = initializer_full->Data();
    }

    return new_component;
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////