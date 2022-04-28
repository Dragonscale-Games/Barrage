/* ======================================================================== */
/*!
 * \file            ComponentAllocator.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

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

      if (component_type == Component::Type::OBJECT_COMPONENT)
      {
        if (objectComponentAllocMap_.find(componentName) != objectComponentAllocMap_.end())
        {
          return;
        }

        objectComponentAllocMap_[componentName] = &ComponentAllocator::AllocateObjectComponentArray<T>;
        objectComponentNames_.push_back(componentName);
      }
      else if (component_type == Component::Type::POOL_COMPONENT)
      {
        if (poolComponentAllocMap_.find(componentName) != poolComponentAllocMap_.end())
        {
          return;
        }

        poolComponentAllocMap_[componentName] = &ComponentAllocator::AllocatePoolComponent<T>;
        poolComponentNames_.push_back(componentName);
      }
    }
  }

  template <typename T>
  ObjectComponent* ComponentAllocator::AllocateObjectComponentArray(unsigned capacity) const
  {
    ObjectComponent* new_component_array = dynamic_cast<ObjectComponent*>(new T);

    new_component_array->Allocate(capacity);

    return new_component_array;
  }

  template <typename T>
  PoolComponent* ComponentAllocator::AllocatePoolComponent(PoolComponent* initializer) const
  {
    T* new_component = new T;
    T* initializer_full = dynamic_cast<T*>(initializer);

    if (initializer_full)
    {
      *new_component = *initializer_full;
    }

    return dynamic_cast<PoolComponent*>(new_component);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentAllocator_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////