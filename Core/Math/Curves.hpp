/* ======================================================================== */
/*!
 * \file            Curves.hpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
     Provides implementations of commonly used parametric curves.

 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Curves_BARRAGE_H
#define Curves_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  /****************************************************************/
  /*!
    \brief
      Interpolates a set of points using an interpolation parameter
      using Nested Linear Interpolation for Bezier Curves.
    \tparam R
      The type used for the interpolation parameter.
    \param t
      The interpolation parameter in the range [0, 1].
    \param S
      The type of the container used to store the points.
      The container must contain
      - An index operator returning objects of type T.
      - A 'size' function returning the number of elements in the 
        container.
    \tparam T
      The type of points interpolated.
      This type must contain
      - A conversion constructor taking in value of type R.
      - An addition operator adding two points of type T, returning
        a third point of type T.
      - A multiplication operator taking in a scalar of type R 
        and a point of type T, returning a point of type T.
    \param points
      A container with random access indexing containing the set
      of points available.
    \returns
      An interpolating point along Bezier curve.
  */
  /****************************************************************/
  template <typename R, typename S, typename T>
  T Bezier(const R& t, const S<T>& points);
}

#include "Curves.tpp"
////////////////////////////////////////////////////////////////////////////////
#endif // Curves_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////
