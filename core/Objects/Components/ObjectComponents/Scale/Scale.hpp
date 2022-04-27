/* ======================================================================== */
/*!
 * \file            Scale.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The 2D scale of an object in world units.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Scale_BARRAGE_H
#define Scale_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ObjectComponent.hpp"

#include <glm/glm.hpp>

namespace Barrage
{
  //! Component data
  struct ScaleData
  {
    glm::vec2 dimensions_; //!< 2D scale in world units
  };

  typedef ObjectComponentDerived<ScaleData> Scale;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scale_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////