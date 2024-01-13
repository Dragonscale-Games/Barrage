/* ======================================================================== */
/*!
 * \file            EditorData.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Holds all runtime settings and other data needed by the editor.
 */
 /* ======================================================================== */

#include "EditorData.hpp"

namespace Barrage
{
  EditorData::EditorData() :
    isRunning_(false),
    gamePlaying_(false),
    sceneIsDirty_(false),
    projectIsDirty_(false),

    openProjectModal_(false),

    gameTick_(0),

    projectName_(),
    projectDirectory_(),
    selectedScene_()
  {
  }
}