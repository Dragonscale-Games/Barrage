/* ======================================================================== */
/*!
 * \file            ShaderManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shader manager for simple renderer.
 */
 /* ======================================================================== */

#include "ShaderManager.hpp"

#include <stdexcept>
#include <fstream>

namespace Barrage
{
  ShaderManager::ShaderManager() :
    shaders_()
  {
  }

  ShaderManager::~ShaderManager()
  {
    for (const auto& i : shaders_)
    {
      delete i.second;
    }
  }

  const Shader* ShaderManager::GetShader(const std::string& name)
  {
    auto shader = shaders_.find(name);

    if (shader == shaders_.end())
    {
      return CreateShader(name);
    }

    return shader->second;
  }

  void ShaderManager::UnloadShaders()
  {
    for (auto shader : shaders_)
    {
      delete shader.second;
    }

    shaders_.clear();
  }

  Shader* ShaderManager::CreateShader(const std::string& name)
  {
    unsigned program_id = CompileShaderProgram(name);

    Shader* new_shader = new Shader(program_id);

    shaders_[name] = new_shader;

    return new_shader;
  }

  unsigned ShaderManager::CompileShaderProgram(const std::string& name)
  {
    unsigned vertex_id = CompileShader(name, GL_VERTEX_SHADER);
    unsigned fragment_id = CompileShader(name, GL_FRAGMENT_SHADER);

    unsigned program_id = LinkShaderProgram(vertex_id, fragment_id);

    return program_id;
  }

  unsigned ShaderManager::CompileShader(const std::string& name, GLenum shaderType)
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

  unsigned ShaderManager::LinkShaderProgram(unsigned vertexID, unsigned fragmentID)
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

  std::string ShaderManager::GetShaderSource(const std::string& path)
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