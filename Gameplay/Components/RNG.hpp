/* ======================================================================== */
/*!
 * \file            RNG.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Random number generator component.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RNG_BARRAGE_H
#define RNG_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/Component.hpp"
#include <Random/Random.hpp>

namespace Barrage
{
  //! Random number generator component
  class RNG
  {
    public:
      Barrage::Random rng_;

      inline RNG() : rng_() {}
  };

  typedef Barrage::ComponentT<RNG> RNGComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // RNG_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////