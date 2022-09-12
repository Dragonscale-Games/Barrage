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
 * \file            SimpleShaderManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shader manager for simple renderer.
 */
 /* ======================================================================== */

#include "SimpleShaderManager.hpp"

#include <stdexcept>
#include <fstream>

namespace Barrage
{
  SimpleShaderManager::SimpleShaderManager() :
    library_()
  {
  }

  SimpleShaderManager::~SimpleShaderManager()
  {
    for (const auto& i : library_)
    {
      delete i.second;
    }
  }

  const SimpleShader* SimpleShaderManager::GetShader(const std::string& name)
  {
    auto shader = library_.find(name);

    if (shader == library_.end())
    {
      return CreateShader(name);
    }

    return shader->second;
  }

  void SimpleShaderManager::UnloadShaders()
  {
    for (auto shader : library_)
    {
      delete shader.second;
    }

    library_.clear();
  }

  SimpleShader* SimpleShaderManager::CreateShader(const std::string& name)
  {
    unsigned program_id = CompileShaderProgram(name);

    SimpleShader* new_shader = new SimpleShader(program_id);

    library_[name] = new_shader;

    return new_shader;
  }

  unsigned SimpleShaderManager::CompileShaderProgram(const std::string& name)
  {
    unsigned vertex_id = CompileShader(name, GL_VERTEX_SHADER);
    unsigned fragment_id = CompileShader(name, GL_FRAGMENT_SHADER);

    unsigned program_id = LinkShaderProgram(vertex_id, fragment_id);

    return program_id;
  }

  unsigned SimpleShaderManager::CompileShader(const std::string& name, GLenum shaderType)
  {
    std::string shader_source;

    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
      shader_source = GetShaderSource("Assets/Shaders/" + name + ".vert");
      break;

    case GL_FRAGMENT_SHADER:
      shader_source = GetShaderSource("Assets/Shaders/" + name + ".frag");
      break;
    }

    const char* buffer = shader_source.c_str();

    unsigned shader_id = glCreateShader(shaderType);
    glShaderSource(shader_id, 1, &buffer, NULL);
    glCompileShader(shader_id);

    int status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);

    if (status == 0)
    {
      std::string error_message = "Shader could not be compiled: ";
      char error_buffer[1024];
      glGetShaderInfoLog(shader_id, 1024, 0, error_buffer);
      error_message += error_buffer;
      throw std::runtime_error(error_message);
    }

    return shader_id;
  }

  unsigned SimpleShaderManager::LinkShaderProgram(unsigned vertexID, unsigned fragmentID)
  {
    unsigned program_id = glCreateProgram();
    glAttachShader(program_id, vertexID);
    glAttachShader(program_id, fragmentID);
    glLinkProgram(program_id);

    int status;
    glGetProgramiv(program_id, GL_LINK_STATUS, &status);

    if (status == 0)
    {
      throw std::runtime_error("Shader program could not be linked.");
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    return program_id;
  }

  std::string SimpleShaderManager::GetShaderSource(const std::string& path)
  {
    std::string file_string;
    std::ifstream infile(path);

    if (!infile.is_open())
    {
      std::string error_message = path + " could not be opened for read.";

      throw std::runtime_error(error_message.c_str());
    }

    while (!infile.eof())
    {
      std::string line;

      std::getline(infile, line);

      file_string += line + "\n";
    }

    return file_string;
  }
}