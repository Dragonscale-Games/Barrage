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

#include "Objects/Components/Component.hpp"

namespace Barrage
{
  //! Holds all information needed to draw the objects in a pool
  class CircleCollider
  {
    public:
      float radius_;

      CircleCollider();

      static void Reflect();
  };

  typedef Barrage::ComponentT<CircleCollider> CircleColliderComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // CircleCollider_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////