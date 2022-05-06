/* ========================================================================= */
/*!
 *
 * \file            Main.cpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu
 
 * \brief
 * Defines the entry point for the editor.
 */
/* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================

#include "Editor/Editor.hpp"

/******************************************************************************/
/*!
  \brief
    Defines the entry point for the application.
*/
/******************************************************************************/
int main(void)
{
  Barrage::Editor* editor = new Barrage::Editor;

  editor->Run();

  delete editor;

  return 0;
}

