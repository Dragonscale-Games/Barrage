/* ======================================================================== */
/*!
 * \file            CircleCollider.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CircleCollider_BARRAGE_H
#define CircleCollider_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/SharedComponent.hpp"
#include <rttr/rttr_enable.h>

namespace Demo
{
  //! Holds all information needed to draw the objects in a pool
  class CircleCollider
  {
    public:
      float radius_;

      CircleCollider() : radius_(50.0f) {}
  };

  typedef Barrage::SharedComponentT<CircleCollider> SharedCircleCollider;
}

////////////////////////////////////////////////////////////////////////////////
#endif // CircleCollider_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////