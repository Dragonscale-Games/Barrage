/* ======================================================================== */
/*!
 * \file            Timer.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Timer_BARRAGE_H
#define Timer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/PoolComponent.hpp"

namespace Barrage
{
  //! <class description>
  class Timer : public PoolComponent
  {
  public:
    Timer();

  public:
    float timer_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Timer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////