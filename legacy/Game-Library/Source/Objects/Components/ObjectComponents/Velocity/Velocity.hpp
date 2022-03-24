/* ======================================================================== */
/*!
 * \file            Velocity.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    2D speed in world units per tick.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Velocity_BARRAGE_H
#define Velocity_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ObjectComponent.hpp"

#include <glm/glm.hpp>

namespace Barrage
{
  //! Component data
  struct VelocityData
  {
    glm::vec2 velocity_; //!< 2D speed in world units per tick
  };

  typedef ObjectComponentDerived<VelocityData> Velocity;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Velocity_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////