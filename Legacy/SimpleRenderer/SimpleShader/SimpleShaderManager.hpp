/*
MIT License

Copyright(c) 2022 Dragonscale-Games

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ======================================================================== */
/*!
 * \file            SimpleShaderManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shader manager class for renderer.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SimpleShaderManager_BARRAGE_H
#define SimpleShaderManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "SimpleShader.hpp"

#include <glad/gl.h>
#include <unordered_map>
#include <string>

namespace Barrage
{
  typedef std::unordered_map<std::string, SimpleShader*> SimpleShaderLibrary;

  //! Temporary shader manager to make it convenient to test game systems.
  class SimpleShaderManager
  {
  public:
    SimpleShaderManager();

    ~SimpleShaderManager();

    const SimpleShader* GetShader(const std::string& name);

    void UnloadShaders();

  private:
    SimpleShaderLibrary library_;

    SimpleShader* CreateShader(const std::string& name);

    unsigned CompileShaderProgram(const std::string& name);

    unsigned CompileShader(const std::string& name, GLenum shaderType);

    unsigned LinkShaderProgram(unsigned vertexID, unsigned fragmentID);

    std::string GetShaderSource(const std::string& path);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SimpleShaderManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////