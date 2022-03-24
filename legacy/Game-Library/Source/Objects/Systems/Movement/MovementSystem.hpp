/* ======================================================================== */
/*!
 * \file            MovementSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef MovementSystem_BARRAGE_H
#define MovementSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/BaseSystem.hpp"

namespace Barrage
{
  //! <class description>
  class MovementSystem : public System
  {
  public:
    /**************************************************************/
    /*!
      \brief
        Initializes system.
    */
    /**************************************************************/
    MovementSystem();

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
#endif // MovementSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////