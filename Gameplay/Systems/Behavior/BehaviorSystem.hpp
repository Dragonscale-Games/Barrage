/* ======================================================================== */
/*!
 * \file            BehaviorSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorSystem_BARRAGE_H
#define BehaviorSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Systems/System.hpp>

namespace Barrage
{
  //! Tells bullets when to spawn
  class BehaviorSystem : public System
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      BehaviorSystem();

      /**************************************************************/
      /*!
        \brief
          Subscribes pools to the behavior system and sets up
          behavior tree.
      */
      /**************************************************************/
      void Subscribe(Space& space, Pool* pool) override;

      /**************************************************************/
      /*!
        \brief
          Executes behaviors.
      */
      /**************************************************************/
      void Update() override;

    private:
      static void ExecuteBehaviorTree(Space& space, Pool& pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////