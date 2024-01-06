/* ======================================================================== */
/*!
 * \file            ObjectManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The main point of contact for game object manipulation.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectManager_BARRAGE_H
#define ObjectManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Systems/SystemManager.hpp"

namespace Barrage
{
  class Space;

  using DrawCallback = void(*)();

  //! Main point of contact for game object manipulation
  class ObjectManager
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor. Registers default engine components,
          systems, and initializers.
      */
      /**************************************************************/
      ObjectManager(Space& space);

      /**************************************************************/
      /*!
        \brief
          Updates all objects.
      */
      /**************************************************************/
      void Update();

      /**************************************************************/
      /*!
        \brief
          Draws all objects.
      */
      /**************************************************************/
      void Draw();

      void CreatePool(const PoolArchetype& archetype);

      void DeleteAllPools();

      void SubscribePools();

      void SetDrawCallback(DrawCallback callback);

    private:
      DrawCallback drawCallback_;
      PoolMap pools_;
      SystemManager systemManager_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////