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
    openComponentModal_(false),
    openComponentArrayModal_(false),
    openTagModal_(false),
    nextScene_(nullptr),
    selectedSpace_(),
    selectedScene_(),
    selectedPool_(),
    selectedObject_(),
    selectedComponent_(),
    selectedComponentArray_(),
    selectedTag_()
  {
  }
}