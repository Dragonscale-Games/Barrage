/* ======================================================================== */
/*!
 * \file            TextureSpaceArray.hpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games\@gmail.com

 * \brief
   The texture space component keeping track of each object's
   position in texture space.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef TextureSpaceArray_BARRAGE_H
#define TextureSpaceArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  //!< World position of an object
  struct TextureSpace
  {
    float u_;     //!< u coord in texture space.
    float v_;     //!< v coord in texture space.
    float uSize_; //!< The texture scale in the u axis.
    float vSize_; //!< The texture scale in the v axis.

    inline TextureSpace() : u_(0.0f), v_(0.0f), uSize_(1.0f), vSize_(1.0f) {}
  };

  typedef ComponentArrayT<TextureSpace> TextureSpaceArray;

  template <>
  inline std::string TextureSpaceArray::GetClassName() { return "TextureSpaceArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // TextureSpaceArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////