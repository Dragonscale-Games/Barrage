/* ======================================================================== */
/*!
 * \file            RNG.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef RNG_BARRAGE_H
#define RNG_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/PoolComponent.hpp"
#include "Random/Random.hpp"

namespace Barrage
{
  //! <class description>
  class RNG : public PoolComponent
  {
  public:
    RNG();

  public:
    Random rng_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RNG_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////