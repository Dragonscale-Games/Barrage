/* ======================================================================== */
/*!
 * \file            Utilities.tpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Miscellaneous utilities for the barrage engine.

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Utilities_BARRAGE_T
#define Utilities_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <math.h>

namespace Barrage
{
  template <typename T>
  T Clamp(T value, T min, T max)
  {
    if (value < min)
      return min;
    else if (value > max)
      return max;
    else
      return value;
  }

  template <typename T>
  T ClampWrapped(T value, T min, T max)
  {
    const T width = max - min;
    const T offset = value - min;

    return (offset - (floor(offset / width) * width)) + min;
  }

  template <typename T>
  T Lerp(T min, T max, float lerpFactor)
  {
    lerpFactor = Clamp(lerpFactor, 0.0f, 1.0f);

    return min + static_cast<T>((max - min) * lerpFactor);
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // Utilities_BARRAGE_T
////////////////////////////////////////////////////////////////////////////////