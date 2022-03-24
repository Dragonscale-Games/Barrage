/* ======================================================================== */
/*!
 * \file            TimerSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TimerSystem_BARRAGE_H
#define TimerSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/BaseSystem.hpp"

namespace Barrage
{
  //! <class description>
  class TimerSystem : public System
  {
  public:
    /**************************************************************/
    /*!
      \brief
        Initializes system.
    */
    /**************************************************************/
    TimerSystem();

  private:
    /**************************************************************/
    /*!
      \brief
        Update function for a single object pool.

      \param pool
        The pool to update.
    */
    /**************************************************************/
    void UpdatePool(Pool* pool) override;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TimerSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////