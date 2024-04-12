/* ======================================================================== */
/*!
 * \file            Sprite.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Information used to texture and draw an object.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Sprite_BARRAGE_H
#define Sprite_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/Component.hpp"

namespace Barrage
{
  //! Holds all information needed to draw the objects in a pool
  class Sprite
  {
    public:
      std::string texture_; //!< Name of the texture to draw with
      unsigned layer_;      //!< Layer of the drawn object (lower layers are drawn beneath higher ones)

      Sprite();

      static void Reflect();
  };

  typedef ComponentT<Sprite> SpriteComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Sprite_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////