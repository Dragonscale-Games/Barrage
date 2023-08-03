/* ======================================================================== */
/*!
 * \file            RttrRegistration.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   RTTR registration.
 */
 /* ======================================================================== */

#include <string>
#include <rttr/registration.h>

#include "Entry/Entry.hpp"

#include "ComponentArrays/RttrComponentArrays.hpp"
#include "Components/RttrComponents.hpp"
#include "SpawnRules/RttrSpawnRules.hpp"

namespace Barrage
{
  void ReflectBarrageCore()
  {
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

    ReflectComponentArrays();
    ReflectComponents();
    ReflectSpawnRules();
  }
}