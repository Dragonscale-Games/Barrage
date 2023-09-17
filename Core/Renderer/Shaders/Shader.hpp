/* ======================================================================== */
/*!
 * \file            Shader.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Represents a shader on the GPU.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Shader_BARRAGE_H
#define Shader_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glad/gl.h>
#include <string>

namespace Barrage
{
  //! Represents a shader on the GPU
  class Shader
  {
    public:
      Shader(const std::string& vertexSource, const std::string& fragmentSource);

      ~Shader();
      
      void Bind();

      static void Unbind();

      GLuint GetID();

    private:
      GLuint id_;

      static GLuint CompileShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);

      static GLuint CompileShader(const std::string& source, GLenum shaderType);

      static GLuint LinkShaderProgram(GLuint vertexID, GLuint fragmentID);

      Shader(const Shader& other) = delete;
      Shader(Shader&& other) = delete;
      Shader& operator=(const Shader& other) = delete;
      Shader& operator=(Shader&& other) = delete;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Shader_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////