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
  void ComponentAllocator::RegisterComponent(const std::string& componentName)
  {
    // create a test component of the input type and make sure it's a component
    T type_test;
    Component* component = dynamic_cast<Component*>(&type_test);

    if (component)
    {
      Component::Type component_type = component->GetType();

      if (component_type == Component::Type::ARRAY)
      {
        if (componentArrayAllocMap_.find(componentName) != componentArrayAllocMap_.end())
        {
          return;
        }

        componentArrayAllocMap_[componentName] = &ComponentAllocator::AllocateComponentArray<T>;
        componentArrayNames_.push_back(componentName);
      }
      else if (component_type == Component::Type::SHARED)
      {
        if (sharedComponentAllocMap_.find(componentName) != sharedComponentAllocMap_.end())
        {
          return;
        }

        sharedComponentAllocMap_[componentName] = &ComponentAllocator::AllocateSharedComponent<T>;
        sharedComponentNames_.push_back(componentName);
      }
    }
  }

  template <typename T>
  ComponentArray* ComponentAllocator::AllocateComponentArray(unsigned capacity) const
  {
    ComponentArray* new_component_array = dynamic_cast<ComponentArray*>(new T);

    new_component_array->Allocate(capacity);

    return new_component_array;
  }

  template <typename T>
  SharedComponent* ComponentAllocator::AllocateSharedComponent(SharedComponent* initializer) const
  {
    T* new_component = new T;
    T* initializer_full = dynamic_cast<T*>(initializer);

    if (initializer_full)
    {
      *new_component = *initializer_full;
    }

    return dynamic_cast<SharedComponent*>(new_component);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////