/* ======================================================================== */
/*!
 * \file            Sprite.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Contains the information needed to draw the objects in an object pool.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Sprite_BARRAGE_H
#define Sprite_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/PoolComponent.hpp"

namespace Barrage
{
	//! Contains the information needed to draw the objects in an object pool
  class Sprite : public PoolComponent
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Initializes sprite with default texture on default layer.
      */
      /**************************************************************/
      Sprite();

    public:
      std::string texture_; //!< Name of the texture to draw with
      unsigned layer_;      //!< Layer of the drawn object (lower layers are drawn beneath higher ones)
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Sprite_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////