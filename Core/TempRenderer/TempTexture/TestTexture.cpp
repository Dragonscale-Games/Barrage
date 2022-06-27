/* ======================================================================== */
/*!
 * \file            TestTexture.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary texture class to make it convenient to test game systems.
 */
 /* ======================================================================== */

#include "stdafx.h"

#include "TestTexture.hpp"

#include <glad/gl.h>

namespace Barrage
{
  TestTexture::TestTexture(unsigned textureID) :
    textureID_(textureID)
  {
  }

  TestTexture::~TestTexture()
  {
    glDeleteTextures(1, &textureID_);
  }

  unsigned TestTexture::GetID() const
  {
    return textureID_;
  }
}