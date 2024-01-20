/* ======================================================================== */
/*!
 * \file            BehaviorNodeFactory.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of behavior node via its name.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorNodeFactory_BARRAGE_T
#define BehaviorNodeFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace Barrage
{
  template <typename T>
  void BehaviorNodeFactory::RegisterBehaviorNode(const std::string& name)
  {
    if (behaviorNodeFactoryMethodMap_.count(name) || !std::is_base_of<BehaviorNode, T>::value)
    {
      return;
    }

    behaviorNodeNames_.insert(name);
    behaviorNodeFactoryMethodMap_[name] = &BehaviorNodeFactory::AllocateBehaviorNode<T>;
  }

  template <typename T>
  BehaviorNodeDeepPtr BehaviorNodeFactory::AllocateBehaviorNode()
  {
    return BehaviorNodeDeepPtr(std::make_shared<T>());
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorNodeFactory_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////