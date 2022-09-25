/* ========================================================================= */
/*!
 *
 * \file            GfxPrimitives.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines a ton of useful functions for generate geometric primitives.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include "GfxPrimitives.hpp"

namespace Barrage
{
  void GenQuadInfo(std::vector<Vertex>& vertices, std::vector<Face>& indices)
  {
    vertices.clear();
    indices.clear();
    
    vertices.push_back(Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(Vertex(glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2( 0.5f,  0.5f), glm::vec2(1.0f, 1.0f)));
    vertices.push_back(Vertex(glm::vec2( 0.5f, -0.5f), glm::vec2(1.0f, 0.0f)));

    indices.push_back(Face(0, 1, 2));
    indices.push_back(Face(2, 3, 0));
  }
}
