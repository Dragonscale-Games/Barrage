/* ======================================================================== */
/*!
 * \file            main.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Entry point for the demo game.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Registration/Registrar.hpp"
#include "Editor.hpp"

#include <string>
#include <rttr/registration.h>

using namespace Barrage;

RTTR_REGISTRATION
{
  Registrar::Reflection();
}

int main(int argc, char* argv[])
{
  std::unique_ptr<Editor> editor = std::make_unique<Editor>();

  editor->Run();

  return 0;
}

