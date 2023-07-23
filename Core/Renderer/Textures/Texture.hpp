/* ======================================================================== */
/*!
 * \file            Texture.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Represents a texture on the GPU.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Texture_BARRAGE_H
#define Texture_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glad/gl.h>
#include <string>

namespace Barrage
{
  //! Texture class for simple renderer
  class Texture
  {
    public:
      Texture();
      
      Texture(const std::string& path, GLint filter = GL_LINEAR);
      
      Texture(int width, int height, const GLubyte* imageData, GLint filter = GL_LINEAR);

      ~Texture();

      void Bind();

      static void Unbind();

      GLuint GetID();

      bool IsValid();

    private:
      unsigned id_;

      static GLuint CreateTexture(const std::string& path, GLint filter = GL_LINEAR);

      static GLuint CreateTexture(int width, int height, const GLubyte* imageData, GLint filter = GL_LINEAR);

      Texture(const Texture& other) = delete;
      Texture(Texture&& other) = delete;
      Texture& operator=(const Texture& other) = delete;
      Texture& operator=(Texture&& other) = delete;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Texture_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////