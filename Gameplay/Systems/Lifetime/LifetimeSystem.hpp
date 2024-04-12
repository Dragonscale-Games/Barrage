/* ======================================================================== */
/*!
 * \file            LifetimeSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles game object lifetimes.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef LifetimeSystem_BARRAGE_H
#define LifetimeSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/System.hpp"

namespace Barrage
{
  //! Handles game object lifetimes
  class LifetimeSystem : public System
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      LifetimeSystem();

      /**************************************************************/
      /*!
         \brief
           Updates system.
      */
      /**************************************************************/
      void Update() override;

    private:
      static void UpdateLifetimes(Space& space, Pool& pool);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // LifetimeSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////