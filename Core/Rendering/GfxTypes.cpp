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

 uint8_t GetChannelCount(const TextureFormat& format)
 {
   // An array of channel counts that map directly for a format.
   const uint8_t channelCounts[] = {
     4, 3, 2, 1,
   };
   return channelCounts[static_cast<uint8_t>(format)];
 }

 size_t GetFormatSize(const TextureFormat& format)
 {
   // An array of format sizes that map directly for a format.
   const size_t formatSizes[] = {
     4 * sizeof(uint8_t),
     3 * sizeof(uint8_t),
     2 * sizeof(uint8_t),
     1 * sizeof(uint8_t),
   };
   return formatSizes[static_cast<uint8_t>(format)];
 }
}
