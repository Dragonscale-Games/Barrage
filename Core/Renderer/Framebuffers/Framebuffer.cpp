/* ======================================================================== */
/*!
 * \file            Framebuffer.Cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Represents a framebuffer on the GPU.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Framebuffer.hpp"

#include <stdexcept>

namespace Barrage
{
  Framebuffer::Framebuffer(GLsizei width, GLsizei height) :
    texId_(0),
    fboId_(0)
  {
    glGenTextures(1, &texId_);
    glBindTexture(GL_TEXTURE_2D, texId_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenFramebuffers(1, &fboId_);
    glBindFramebuffer(GL_FRAMEBUFFER, fboId_);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId_, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
    {
      throw std::runtime_error("Incomplete framebuffer.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  Framebuffer::~Framebuffer()
  {
    glDeleteFramebuffers(1, &fboId_);
    glDeleteTextures(1, &texId_);
  }

  void Framebuffer::BindFramebuffer()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, fboId_);
  }

  void Framebuffer::UnbindFramebuffer()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void Framebuffer::BindTexture()
  {
    glBindTexture(GL_TEXTURE_2D, texId_);
  }

  void Framebuffer::UnbindTexture()
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void Framebuffer::Resize(GLsizei width, GLsizei height)
  {
    glBindTexture(GL_TEXTURE_2D, texId_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
    {
      throw std::runtime_error("Framebuffer resize failed (incomplete framebuffer error).");
    }
  }

  GLuint Framebuffer::GetFramebufferID()
  {
    return fboId_;
  }

  GLuint Framebuffer::GetTextureID()
  {
    return texId_;
  }
}