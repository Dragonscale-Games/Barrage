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

#include "Objects/Components/ComponentArray.hpp"

namespace Barrage
{
  static const float MINIMUM_SPEED = 0.000001f;
  
  //!< Speed and direction of a game object
  struct Velocity
  {
    float vx_; //!< x speed in world units per tick
    float vy_; //!< y speed in world units per tick

    Velocity();

    static void Reflect();
  };

  typedef Barrage::ComponentArrayT<Velocity> VelocityArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // VelocityArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////