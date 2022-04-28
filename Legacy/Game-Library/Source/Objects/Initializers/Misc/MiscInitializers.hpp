/* ======================================================================== */
/*!
 * \file            MiscInitializers.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef MiscInitializers_BARRAGE_H
#define MiscInitializers_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Pools/Pool.hpp"

namespace Barrage
{
  namespace Initializers
  {
    void CircleSpawn(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects);

    void RandomDirection(Pool& initPool, Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // MiscInitializers_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////