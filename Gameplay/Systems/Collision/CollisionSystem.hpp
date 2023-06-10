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
  class CollisionSystem : public Barrage::System
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
    static void UpdateBoundedBullets(Barrage::Pool* pool);
    
    static void UpdatePlayerBulletCollisions(Barrage::Pool* player_pool, Barrage::Pool* bullet_pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CollisionSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////