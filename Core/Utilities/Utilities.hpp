/* ======================================================================== */
/*!
 * \file            Utilities.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Miscellaneous utilities for the barrage engine.

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Utilities_BARRAGE_H
#define Utilities_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  typedef float RADIAN;
  typedef float DEGREE;
  
  /**************************************************************/
  /*!
    \brief
      Clamps a value to a range by setting it to the min or max
      of the range if the input value is outside the range.

    \tparam T
      The type of the value to clamp.

    \param value
      The input value to clamp.

    \param min
      The minimum value of the range.

    \param max
      The maximum value of the range.

    \return
      Returns min if the input value is lower than min, returns 
      max if the input value is greater than max, and returns the
      input value otherwise.
  */
  /**************************************************************/
  template <typename T>
  T Clamp(T value, T min, T max);

  /**************************************************************/
  /*!
    \brief
      Clamps a value by assuming the range wraps around when below
      min or above max. Useful for angles. 

      For instance, the wrapped value of 400 in the range [0, 360)
      is 40 (i.e. 400 degrees is equivalent to 40 degrees). 

    \tparam T
      The type of the value to clamp.

    \param value
      The input value to clamp.

    \param min
      The minimum value of the range.

    \param max
      The maximum value of the range.

    \return
      Returns a wrapped value within the range.
  */
  /**************************************************************/
  template <typename T>
  T ClampWrapped(T value, T min, T max);

  /**************************************************************/
  /*!
    \brief
      Linearly interpolates (lerps) between two values. 

    \tparam T
      The type of the values to lerp between.

    \param min
      The minimum value in the range.

    \param max
      The maximum value in the range.

    \param factor
      The linear interpolation factor, interpreted as a percentage.
      A factor of 0.0f will cause the function to return min, and 
      a factor of 1.0f will return max.

    \return
      Returns the linearly interpolated value.
  */
  /**************************************************************/
  template <typename T>
  T Lerp(T min, T max, float factor);
}

#include "Utilities.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Utilities_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////