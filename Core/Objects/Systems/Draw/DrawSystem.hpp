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

#include "Objects/Systems/BaseSystem.hpp"

namespace Barrage
{
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
      void Subscribe(Pool* pool) override;

      /**************************************************************/
      /*!
        \brief
          Draws all pools contained in the system.
      */
      /**************************************************************/
      void Draw();
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // DrawSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////