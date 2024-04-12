/* ======================================================================== */
/*!
 * \file            DrawSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Responsible for sending object draw calls to the renderer.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DrawSystem_BARRAGE_H
#define DrawSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/System.hpp"

namespace Barrage
{
  typedef std::map<unsigned, std::vector<Pool*>> DrawPoolMap;

  //! Responsible for sending object draw calls to the renderer
  class DrawSystem : public System
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      DrawSystem();

      /**************************************************************/
      /*!
        \brief
          Determines if the given object pool has drawable objects
          and, if so, subscribes it to the system.

          Also sorts object pools into buckets depending on their
          draw layer.
      */
      /**************************************************************/
      void Subscribe(Space& space, Pool* pool) override;

      /**************************************************************/
      /*!
        \brief
          Unsubscribes a pool from the system.
      */
      /**************************************************************/
      void Unsubscribe(Space& space, Pool* pool) override;

      /**************************************************************/
      /*!
        \brief
          Draws all pools contained in the system.
      */
      /**************************************************************/
      void Draw();

    private:
      DrawPoolMap drawPools_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DrawSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////