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
    
    bool isRunning_;                  //!< Keeps track of whether the editor is running
    bool sceneIsDirty_;               //!< Flag for when user changes something in current scene
    std::string_view selectedPool_;   //!< The currently selected pool
    std::string_view selectedObject_; //!< The currently selected object
    std::string_view selectedScene_;  //!< The currently selected scene
    std::string_view selectedSpace_;  //!< The currently selected space
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////