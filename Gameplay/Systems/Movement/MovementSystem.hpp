/* ======================================================================== */
/*!
 * \file            MovementSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles game object movement.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef MovementSystem_BARRAGE_H
#define MovementSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/System.hpp"

namespace Barrage
{
  //! Handles game object movement
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
      static void UpdatePlayerMovement(Space& space, Pool& pool);

      static void UpdatePlayerBounds(Space& space, Pool& pool);

      static void UpdateBasicMovement(Space& space, Pool& pool);

      static void UpdateBasicRotation(Space& space, Pool& pool);

      static void UpdateMovement(Space& space, Pool& pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // MovementSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////