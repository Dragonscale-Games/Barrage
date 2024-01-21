/* ======================================================================== */
/*!
 * \file            Registrar.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of system via its name.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Registrar.hpp"

#include "Objects/Behavior/BehaviorTree.hpp"
#include "Scenes/Scene.hpp"
#include "Entry/Entry.hpp"

#include <string>
#include <rttr/variant.h>
#include <rttr/registration.h>

#include "glm/glm.hpp"

namespace Barrage
{
  std::vector<std::string> Registrar::systemUpdateOrder_ = std::vector<std::string>();
  
  void Registrar::Registration()
  {
    CoreRegistration();
    GameplayRegistration();
  }

  void Registrar::Reflection()
  {
    CoreReflection();
    GameplayReflection();
  }

  void Registrar::CoreRegistration()
  {

  }

  void Registrar::CoreReflection()
  {
    rttr::registration::class_<Scene>("Scene")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("name", &Scene::name_)
      .property("poolArchetypes", &Scene::poolArchetypes_)
      ;

    rttr::registration::class_<PoolArchetype>("PoolArchetype")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("capacity", &PoolArchetype::capacity_)
      .property("componentArrayNames", &PoolArchetype::componentArrayNames_)
      .property("components", &PoolArchetype::components_)
      .property("name", &PoolArchetype::name_)
      .property("spawnArchetypes", &PoolArchetype::spawnArchetypes_)
      .property("startingObjects", &PoolArchetype::startingObjects_)
      .property("tags", &PoolArchetype::tags_)
      ;

    rttr::registration::class_<ObjectArchetype>("ObjectArchetype")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("name", &ObjectArchetype::name_)
      .property("componentArrays", &ObjectArchetype::componentArrays_)
      ;

    rttr::registration::class_<Radian>("Radian")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("value", &Radian::value_)
      ;

    rttr::registration::class_<Entry::SpaceEntry>("SpaceEntry")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("Name", &Entry::SpaceEntry::name_)
      .property("Scene", &Entry::SpaceEntry::scene_)
      ;

    rttr::registration::class_<Entry>("Entry")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("Spaces", &Entry::spaces_)
      .property("Textures", &Entry::textures_)
      ;

    rttr::registration::class_<glm::vec2>("glm::vec2")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("x", &glm::vec2::x)
      .property("y", &glm::vec2::y)
      ;

    rttr::registration::class_<BehaviorTree>("BehaviorTree")
      .constructor<>() (rttr::policy::ctor::as_object)
      .property("recipe", &BehaviorTree::recipe_)
      ;
  }

  std::vector<std::string>& Registrar::GetSystemUpdateOrder()
  {
    return systemUpdateOrder_;
  }

  void Registrar::RegisterTag(const std::string& tag)
  {
    ComponentFactory::RegisterTag(tag);
  }

  void Registrar::SetSystemUpdateOrder(const std::vector<std::string>& updateOrder)
  {
    systemUpdateOrder_ = updateOrder;
  }
}
