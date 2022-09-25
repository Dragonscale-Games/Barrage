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

#include "Objects/Components/BaseClasses/SharedComponent.hpp"
#include <Random/Random.hpp>

namespace Demo
{
  //! Random number generator component
  class RNG : public Barrage::SharedComponent
  {
    public:
      Barrage::Random rng_;

      inline RNG() : rng_() {}

      inline std::string GetClassName() override { return "RNG"; }

      RTTR_ENABLE()
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RNG_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////