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

#include "Objects/Systems/BaseSystem.hpp"

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
        Determines if the given object pool has a collider and, if
        so, subscribes it to the system.

        Also sorts object pools into buckets depending on its tags
        to handle different types of collisions.

        For instance, object pools with the "Player" tag are sorted
        into a different bucket than pools with the "Bullet" tag.
        Each "Player" pool checks for collisions against every
        "Bullet" pool, and that specific type of collision is
        handled.
    */
    /**************************************************************/
    void Subscribe(Pool* pool) override;

    /**************************************************************/
    /*!
      \brief
        Iterates through each collider bucket and handles collisions
        against pools in the other buckets.
    */
    /**************************************************************/
    void Update() override;

  private:
    void UpdatePlayerBulletCollisions(Pool* player_pool, Pool* bullet_pool);

    void UpdateMetaballWallCollisions(Pool* metaball_pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CollisionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////