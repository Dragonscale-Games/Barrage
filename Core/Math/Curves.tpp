/* ======================================================================== */
/*!
 * \file            Curves.tpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
     Provides implementations of commonly used parametric curves.

 */
 /* ======================================================================== */

#include "Curves.hpp"
#include <Utilities/RecursionTable.hpp>

namespace Barrage
{
  template <typename R, typename S, typename T>
  T Bezier(const R& t, const S<T>& points)
  {
    static RecursionTable<T> table;
    table.Resize(points.size());
    // Set the initial condition for the recursive statement.
    for (uint32_t i = 0; i < points.size(); ++i)
    {
      table[0][i] = points[i];
    }
    // Then, recursively, solve for our interpolation point.
    // Gets the number of rows.
    uint32_t rows = table.GetRows();
    for (uint32_t i = 1; i < rows; ++i)
    {
      uint32_t rowSize = table.GetRowSize(i);
      for (uint32_t j = 0; j < rowSize; ++j)
      {
        table[i][j] = (R(1) - t) * table[i - 1][j] + (t) * table[i - 1][j + 1];
      }
    }
  }
  // Return the last element in the table, containing the answer.
  return table.Back();
}
