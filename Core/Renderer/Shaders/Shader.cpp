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

#include "Shader.hpp"

#include <glad/gl.h>

namespace Barrage
{
  Shader::Shader(unsigned programID) :
    programID_(programID)
  {
  }

  Shader::~Shader()
  {
    glDeleteProgram(programID_);
  }

  unsigned Shader::GetID() const
  {
    return programID_;
  }
}