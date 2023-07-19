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

#include "Editor.hpp"

#include <rttr/registration.h>
#include <Serialization/ComponentRefl.hpp>
#include <string>

RTTR_REGISTRATION
{
  // Reflect all the core Barrage objects.
  Barrage::ReflectBarrageCore();
}

int main(int argc, char* argv[])
{
  std::string project_path;
  
  if (argc > 1)
  {
    project_path = argv[1];
  }
  
  Barrage::Editor* editor = new Barrage::Editor;

  editor->Run(project_path);

  delete editor;

  return 0;
}

