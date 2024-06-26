/* ======================================================================== */
/*!
 * \file            CollisionSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef CollisionSystem_BARRAGE_H
#define CollisionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/System.hpp"

namespace Barrage
{
  //! <class description>
  class CollisionSystem : public System
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      CollisionSystem();

      /**************************************************************/
      /*!
        \brief
          Iterates through each collider bucket and handles collisions
          against pools in the other buckets.
      */
      /**************************************************************/
      void Update() override;

    private:
      static void UpdateBoundedBullets(Space& space, Pool& pool);
      
      static void UpdatePlayerBulletCollisions(Space& space, Pool& player_pool, Pool& bullet_pool);

      static void ClearBulletsOnPlayerHit(Space& space, Pool& player_pool, Pool& bullet_pool);

      static void ResetPlayerHit(Space& space, Pool& pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CollisionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////