/* ======================================================================== */
/*!
 * \file            Sprite.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Sprite_BARRAGE_H
#define Sprite_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/Component.hpp"

namespace Barrage
{
  //! Holds all information needed to draw the objects in a pool
  class Sprite
  {
    public:
      std::string texture_; //!< Name of the texture to draw with
      unsigned layer_;      //!< Layer of the drawn object (lower layers are drawn beneath higher ones)

      inline Sprite() : texture_("<default>"), layer_(0) {}
  };

  typedef ComponentT<Sprite> SpriteComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Sprite_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////