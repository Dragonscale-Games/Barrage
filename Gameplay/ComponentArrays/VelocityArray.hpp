/* ======================================================================== */
/*!
 * \file            VelocityArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The Velocity component keeps track of the speed and direction of a game
   object.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef VelocityArray_BARRAGE_H
#define VelocityArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  static const float MINIMUM_SPEED = 0.000001f;
  
  //!< Speed and direction of a game object
  struct Velocity
  {
    float vx_; //!< x speed in world units per tick
    float vy_; //!< y speed in world units per tick

    inline Velocity() : vx_(0.0f), vy_(0.0f) {}
  };

  typedef Barrage::ComponentArrayT<Velocity> VelocityArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // VelocityArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////