/* ======================================================================== */
/*!
 * \file            Movement.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Movement controller component.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Movement_BARRAGE_H
#define Movement_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/Component.hpp"
#include "Math/Curves/BezierCurve.hpp"

namespace Barrage
{
  //! Movement controller
  class Movement
  {
    public:
      BezierCurve curve_;
      double currentTicks_;
      double numTicks_;

      Movement();

      static void Reflect();
  };

  typedef Barrage::ComponentT<Movement> MovementComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Movement_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////