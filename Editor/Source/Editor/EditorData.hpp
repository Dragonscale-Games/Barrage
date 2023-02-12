/* ======================================================================== */
/*!
 * \file            EditorData.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Holds all runtime settings and other data needed by the editor.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef EditorData_BARRAGE_H
#define EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string_view>

namespace Barrage
{
  //! Editor data
  struct EditorData
  {
    EditorData();
    
    bool isRunning_;             //!< Keeps track of whether the editor is running
    bool gamePlaying_;           //!< Keeps track of whether the current game is playing
    bool sceneIsDirty_;          //!< Flag for when user changes something in current scene
    std::string selectedPool_;   //!< The currently selected pool
    std::string selectedObject_; //!< The currently selected object
    std::string selectedScene_;  //!< The currently selected scene
    std::string selectedSpace_;  //!< The currently selected space
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////