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

#include "../BaseClasses/SharedComponent.hpp"
#include <Random/Random.hpp>

namespace Barrage
{
  //! Random number generator component
  class RNG : public SharedComponent
  {
    public:
      Random rng_;

      inline RNG() : rng_() {}

      inline std::string GetClassName() override { return "RNG"; }
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RNG_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////