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

#include "../BaseClasses/SharedComponent.hpp"
#include <rttr/rttr_enable.h>

namespace Barrage
{
  //! Holds all information needed to draw the objects in a pool
  class CircleCollider : public SharedComponent
  {
    public:
      float radius_;

      CircleCollider() : radius_(50.0f) {}

      inline std::string GetClassName() override { return "CircleCollider"; }

      // Notify rttr of the component hierarchy.
      RTTR_ENABLE()
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CircleCollider_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////