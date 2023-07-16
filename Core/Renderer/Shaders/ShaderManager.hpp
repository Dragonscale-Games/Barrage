/* ======================================================================== */
/*!
 * \file            ShaderManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shader manager class for renderer.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ShaderManager_BARRAGE_H
#define ShaderManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Shader.hpp"

#include <glad/gl.h>
#include <unordered_map>
#include <string>

namespace Barrage
{
  typedef std::unordered_map<std::string, Shader*> ShaderLibrary;

  //! Temporary shader manager to make it convenient to test game systems.
  class ShaderManager
  {
  public:
    ShaderManager();

    ~ShaderManager();

    const Shader* GetShader(const std::string& name);

    void UnloadShaders();

  private:
    ShaderLibrary library_;

    Shader* CreateShader(const std::string& name);

    unsigned CompileShaderProgram(const std::string& name);

    unsigned CompileShader(const std::string& name, GLenum shaderType);

    unsigned LinkShaderProgram(unsigned vertexID, unsigned fragmentID);

    std::string GetShaderSource(const std::string& path);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ShaderManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////