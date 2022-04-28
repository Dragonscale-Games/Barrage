/* ======================================================================== */
/*!
 * \file            TestShader.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary shader class to make it convenient to test game systems.
 */
 /* ======================================================================== */

#include "stdafx.h"

#include "TestShader.hpp"

#include <glad/gl.h>

namespace Barrage
{
  TestShader::TestShader(unsigned programID) :
    programID_(programID)
  {
  }

  TestShader::~TestShader()
  {
    glDeleteProgram(programID_);
  }

  unsigned TestShader::GetID() const
  {
    return programID_;
  }
}