/* ========================================================================= */
/*!
 *
 * \file            ComponentRefl.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Provides the reflection data for components in Barrage.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================

#include <rttr/registration.h>
#include <Objects/Components/SharedComponents/CircleCollider.hpp>
#include <iostream>

#define STRINGIFY(X) #X

RTTR_REGISTRATION
{
  std::cout << "Registering Components from RTTR..." << std::endl;
  // Circle Collider
  using Barrage::CircleCollider;
  rttr::registration::class_<CircleCollider>("CircleCollider")
    .property("radius", &CircleCollider::radius_);
}
