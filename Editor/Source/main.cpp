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

#include "Editor/Editor.hpp"

#include <rttr/registration.h>
#include <Serialization/ComponentRefl.hpp>

RTTR_REGISTRATION
{
  // Reflect all the core Barrage objects.
  Barrage::ReflectBarrageCore();
}

int main(void)
{
  Barrage::Editor* editor = new Barrage::Editor;

  editor->Run();

  delete editor;

  return 0;
}

