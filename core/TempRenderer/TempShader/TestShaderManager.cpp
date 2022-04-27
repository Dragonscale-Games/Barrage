/* ======================================================================== */
/*!
 * \file            TestShaderManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary shader manager to make it convenient to test game systems.
 */
 /* ======================================================================== */

#include "stdafx.h"

#include "TestShaderManager.hpp"

#include <stdexcept>
#include <fstream>

namespace Barrage
{
  TestShaderManager& TestShaderManager::Instance()
  {
    static TestShaderManager instance;
    return instance;
  }

  TestShaderManager::TestShaderManager() :
    library_()
  {
  }

  TestShaderManager::~TestShaderManager()
  {
    for (const auto& i : library_)
    {
      delete i.second;
    }
  }

  const TestShader* TestShaderManager::GetShader(const std::string& name)
  {
    auto shader = library_.find(name);

    if (shader == library_.end())
    {
      return CreateShader(name);
    }

    return shader->second;
  }

  void TestShaderManager::UnloadShaders()
  {
    for (auto shader : library_)
    {
      delete shader.second;
    }

    library_.clear();
  }

  TestShader* TestShaderManager::CreateShader(const std::string& name)
  {
    unsigned program_id = CompileShaderProgram(name);

    TestShader* new_shader = new TestShader(program_id);

    library_[name] = new_shader;

    return new_shader;
  }

  unsigned TestShaderManager::CompileShaderProgram(const std::string& name)
  {
    unsigned vertex_id = CompileShader(name, GL_VERTEX_SHADER);
    unsigned fragment_id = CompileShader(name, GL_FRAGMENT_SHADER);

    unsigned program_id = LinkShaderProgram(vertex_id, fragment_id);

    return program_id;
  }

  unsigned TestShaderManager::CompileShader(const std::string& name, GLenum shaderType)
  {
    std::string shader_source;

    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
      shader_source = /*"#version 330 core\n\
                       layout(location = 0) in vec3 a_position;\
                       layout(location = 1) in vec2 a_tex_coord;\
                       uniform mat4 proj_matrix;\
                       uniform mat4 view_matrix;\
                       uniform mat4 transform_matrix;\
                       out vec2 tex_coord;\
                       void main()\
                       {\
                         gl_Position = proj_matrix * view_matrix * transform_matrix * vec4(a_position, 1.0f);\
                         tex_coord = a_tex_coord;\
                       }";*/
                       GetShaderSource("Assets/Shaders/Temporary/" + name + ".vert");
      break;

    case GL_FRAGMENT_SHADER:
      shader_source = /*"#version 330 core\n\
                      out vec4 color;\
                      in vec2 tex_coord;\
                      uniform sampler2D tex_sampler;\
                      void main()\
                      {\
                        color = texture(tex_sampler, tex_coord);\
                      }";*/
                      GetShaderSource("Assets/Shaders/Temporary/" + name + ".frag");
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
      char info_buffer[1024];
      glGetShaderInfoLog(shader_id, 1024, 0, info_buffer);
      error_message += info_buffer;
      throw std::runtime_error(error_message);
    }

    return shader_id;
  }

  unsigned TestShaderManager::LinkShaderProgram(unsigned vertexID, unsigned fragmentID)
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

  std::string TestShaderManager::GetShaderSource(const std::string& path)
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