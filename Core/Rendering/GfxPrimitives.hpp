/* ========================================================================= */
/*!
 *
 * \file            GfxPrimitives.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines a ton of useful functions for generate geometric primitives.
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef GfxPrimitives_MODULE_H
#define GfxPrimitives_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <vector>
#include "GfxTypes.hpp"

namespace Barrage
{
  /****************************************************************************/
  /*!
    \brief
      Generates the vertex information ito generate a quad mesh.
    \param vertices
      A reference to a vector to store the vertices data.
    \param indices
      A reference to a vector to store the face indexing data.
  */
  /****************************************************************************/
  void GenQuadInfo(std::vector<Vertex>& vertices, std::vector<Face>& indices);
}

#endif // GfxPrimitives_MODULE_H
