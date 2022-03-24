/* ======================================================================== */
/*!
 * \file            Destructible.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Tracks whether an object should be destroyed.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Destructible_BARRAGE_H
#define Destructible_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ObjectComponent.hpp"

namespace Barrage
{
  struct DestructibleData
  {
    bool destroyed_;
  };

  typedef ObjectComponentDerived<DestructibleData> Destructible;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Destructible_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////