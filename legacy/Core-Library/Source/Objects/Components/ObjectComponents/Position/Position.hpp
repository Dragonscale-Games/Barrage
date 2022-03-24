/* ======================================================================== */
/*!
 * \file            Position.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The 2D position of an object in world units.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Position_BARRAGE_H
#define Position_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ObjectComponent.hpp"

#include <glm/glm.hpp>

namespace Barrage
{
  //! Component data
  struct PositionData
  {
    glm::vec2 position_; //!< 2D position in world units
  };

  typedef ObjectComponentDerived<PositionData> Position;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Position_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////