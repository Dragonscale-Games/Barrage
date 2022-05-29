/* ========================================================================= */
/*!
 *
 * \file            GfxTypes.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Encompasses utility functions for graphics programs.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include "GfxTypes.hpp"

namespace Barrage
{
 Vertex::Vertex() :
    position_(0.0f), uvCoordinate_(0.0f)
 {
 }

 Vertex::Vertex(const glm::vec2& position, const glm::vec2& uvCoordinate) :
   position_(position), uvCoordinate_(uvCoordinate)
 {
 }

 Face::Face() :
   vertices_{ 0u, 0u, 0u }
 {
 }

 Face::Face(unsigned vertex1, unsigned vertex2, unsigned vertex3) :
    vertex1_(vertex1), vertex2_(vertex2), vertex3_(vertex3)
 {
 }
}
