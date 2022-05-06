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

int main(void)
{
  Barrage::Editor* editor = new Barrage::Editor;

  editor->Run();

  delete editor;

  return 0;
}

