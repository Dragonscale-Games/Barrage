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

#include "../BaseSystem.hpp"

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

    /**************************************************************/
    /*!
       \brief
         Updates movement system.
    */
    /**************************************************************/
    void Update() override;

  private:
    static void UpdatePlayerMovement(Pool* pool);

    static void UpdatePlayerBounds(Pool* pool);

    static void UpdateBasicMovement(Pool* pool);

    static void UpdateBasicRotation(Pool* pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // MovementSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////