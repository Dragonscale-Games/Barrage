/* ======================================================================== */
/*!
 * \file            BoundaryBox.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BoundaryBox_BARRAGE_H
#define BoundaryBox_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/Component.hpp"

namespace Barrage
{
  //! Holds all information needed to draw the objects in a pool
  class BoundaryBox
  {
    public:
      float xMin_;
      float xMax_;
      float yMin_;
      float yMax_;

      BoundaryBox();

      static void Reflect();
  };

  typedef Barrage::ComponentT<BoundaryBox> BoundaryBoxComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // BoundaryBox_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////