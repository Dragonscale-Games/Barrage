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

#include <stb_image/stb_image.h>
#include <glad/gl.h>
#include <stdexcept>

namespace Barrage
{
  Texture::Texture() :
    id_(0)
  {
  }
  
  Texture::Texture(const std::string& path, GLint filter) :
    id_(CreateTexture(path, filter))
  {
  }

  Texture::Texture(int width, int height, const GLubyte* imageData, GLint filter) :
    id_(CreateTexture(width, height, imageData, filter))
  {
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &id_);
  }

  void Texture::Bind()
  {
    glBindTexture(GL_TEXTURE_2D, id_);
  }

  void Texture::Unbind()
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  GLuint Texture::GetID()
  {
    return id_;
  }

  bool Texture::IsValid()
  {
    return id_ != 0;
  }

  GLuint Texture::CreateTexture(const std::string& path, GLint filter)
  {
    int width, height, channels;

    GLubyte* imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!imageData)
    {
      return 0;
    }

    GLuint id = CreateTexture(width, height, imageData, filter);

    stbi_image_free(imageData);

    return id;
  }

  GLuint Texture::CreateTexture(int width, int height, const GLubyte* imageData, GLint filter)
  {
    GLuint id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    return id;
  }
}