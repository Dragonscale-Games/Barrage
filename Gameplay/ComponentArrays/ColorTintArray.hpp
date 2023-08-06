/* ======================================================================== */
/*!
 * \file            ColorTintArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Determines the tint of game objects.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ColorTintArray_BARRAGE_H
#define ColorTintArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/ComponentArray.hpp"

namespace Barrage
{
  //!< Color tint of an object
  struct ColorTint
  {
    float red_;
    float green_;
    float blue_;
    float alpha_;

    inline ColorTint() : red_(0.0f), green_(0.0f), blue_(0.0f), alpha_(1.0f) {}
  };

  typedef Barrage::ComponentArrayT<ColorTint> ColorTintArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // ColorTintArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////