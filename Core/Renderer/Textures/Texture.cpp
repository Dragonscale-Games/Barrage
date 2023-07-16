/* ======================================================================== */
/*!
 * \file            Texture.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture class for simple renderer.
 */
 /* ======================================================================== */

#include "Texture.hpp"

#include <glad/gl.h>

namespace Barrage
{
  Texture::Texture(unsigned textureID) :
    textureID_(textureID)
  {
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &textureID_);
  }

  unsigned Texture::GetID() const
  {
    return textureID_;
  }
}