/* ======================================================================== */
/*!
 * \file            CircleCollider.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Circular collider with a radius in world units.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef CircleCollider_BARRAGE_H
#define CircleCollider_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ObjectComponent.hpp"

namespace Barrage
{
  //! Component data
  struct CircleColliderData
  {
    float radius_; //!< Radius in world units
  };

  typedef ObjectComponentDerived<CircleColliderData> CircleCollider;
}

////////////////////////////////////////////////////////////////////////////////
#endif // CircleCollider_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////