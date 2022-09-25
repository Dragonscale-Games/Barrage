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

namespace Demo
{
  //! <class description>
  class MovementSystem : public Barrage::System
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
    static void UpdatePlayerMovement(Barrage::Pool* pool);

    static void UpdatePlayerBounds(Barrage::Pool* pool);

    static void UpdateBasicMovement(Barrage::Pool* pool);

    static void UpdateBasicRotation(Barrage::Pool* pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // MovementSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////