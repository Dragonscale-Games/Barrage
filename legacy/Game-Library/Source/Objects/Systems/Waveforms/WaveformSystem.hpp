/* ======================================================================== */
/*!
 * \file            WaveformSystem.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef WaveformSystem_BARRAGE_H
#define WaveformSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Systems/BaseSystem.hpp"

namespace Barrage
{
	//! <class description>
  class WaveformSystem : public System
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes system.
      */
      /**************************************************************/
      WaveformSystem();
      
      /**************************************************************/
      /*!
        \brief
          Subscribes a pool if the pool has the tag "WaveDot".

        \param pool
          The pool to subscribe.
      */
      /**************************************************************/
      void Subscribe(Pool* pool) override;

    private:
      /**************************************************************/
      /*!
        \brief
          Update function for a single object pool.

        \param pool
          The pool to update.
      */
      /**************************************************************/
      void UpdatePool(Pool* pool) override;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // WaveformSystem_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////