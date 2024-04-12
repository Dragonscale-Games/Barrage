/* ======================================================================== */
/*!
 * \file            Shader.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shader class for simple renderer.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Shader.hpp"

#include <glad/gl.h>
#include <stdexcept>

namespace Barrage
{
  Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) :
    id_(CompileShaderProgram(vertexSource, fragmentSource))
  {
  }

  Shader::~Shader()
  {
    glDeleteProgram(id_);
  }

  void Shader::Bind()
  {
    glUseProgram(id_);
  }

  void Shader::Unbind()
  {
    glUseProgram(0);
  }

  GLuint Shader::GetID()
  {
    return id_;
  }

  GLuint Shader::CompileShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
  {
    GLuint vertex_id = CompileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragment_id = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

    GLuint program_id = LinkShaderProgram(vertex_id, fragment_id);

    return program_id;
  }

  GLuint Shader::CompileShader(const std::string& source, GLenum shaderType)
  {
    const char* buffer = source.c_str();

    GLuint shader_id = glCreateShader(shaderType);
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

  GLuint Shader::LinkShaderProgram(GLuint vertexID, GLuint fragmentID)
  {
    GLuint program_id = glCreateProgram();
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
}