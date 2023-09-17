/* ======================================================================== */
/*!
 * \file            Framebuffer.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Represents a framebuffer on the GPU.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Framebuffer_BARRAGE_H
#define Framebuffer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glad/gl.h>

namespace Barrage
{
  //! Represents a framebuffer on the GPU
  class Framebuffer
  {
    public:
      Framebuffer(GLsizei width, GLsizei height);
   
      ~Framebuffer();
      
      void BindFramebuffer();

      static void UnbindFramebuffer();

      void BindTexture();

      static void UnbindTexture();

      void Resize(GLsizei width, GLsizei height);

      GLuint GetFramebufferID();

      GLuint GetTextureID();
      
    private:
      GLuint texId_;
      GLuint fboId_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Framebuffer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////