/* ======================================================================== */
/*!
 * \file            TestShaderManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary shader manager to make it convenient to test game systems.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TestShaderManager_BARRAGE_H
#define TestShaderManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "TestShader.hpp"

//#include <glad/glad.h>
#include <glad/gl.h>
#include <unordered_map>
#include <string>

namespace Barrage
{
  typedef std::unordered_map<std::string, TestShader*> TestShaderLibrary;

  //! Temporary shader manager to make it convenient to test game systems.
  class TestShaderManager
  {
  public:
    static TestShaderManager& Instance();

    ~TestShaderManager();

    TestShaderManager(TestShaderManager& other) = delete;

    void operator=(const TestShaderManager& rhs) = delete;

    const TestShader* GetShader(const std::string& name);

    void UnloadShaders();

  private:
    TestShaderLibrary library_;

    TestShaderManager();

    TestShader* CreateShader(const std::string& name);

    unsigned CompileShaderProgram(const std::string& name);

    unsigned CompileShader(const std::string& name, GLenum shaderType);

    unsigned LinkShaderProgram(unsigned vertexID, unsigned fragmentID);

    std::string GetShaderSource(const std::string& path);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TestShaderManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////