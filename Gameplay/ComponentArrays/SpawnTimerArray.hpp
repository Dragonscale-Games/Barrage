/* ======================================================================== */
/*!
 * \file            SpawnTimerArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Keeps track of the number of ticks since a spawn pattern started.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnTimerArray_BARRAGE_H
#define SpawnTimerArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/ComponentArray.hpp"

namespace Barrage
{
  //!< Number of ticks since a spawn pattern started
  struct SpawnTimer
  {
    unsigned ticks_;

    inline SpawnTimer() : ticks_(0) {}
  };

  typedef ComponentArrayT<SpawnTimer> SpawnTimerArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnTimerArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////