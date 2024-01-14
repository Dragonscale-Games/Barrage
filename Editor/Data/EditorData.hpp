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

#include <Scenes/Scene.hpp>
//#include "Widgets/Modals/Rename/RenameModal.hpp"

namespace Barrage
{
  //! Editor data
  struct EditorData
  {
    EditorData();

    bool isRunning_;                          //!< Keeps track of whether the editor is running
    bool gamePlaying_;                        //!< Keeps track of whether the game is playing
    bool sceneIsDirty_;                       //!< Flag for when user changes something in current scene
    bool projectIsDirty_;                     //!< Flag for whether project has changed since the last save

    bool openProjectModal_;                   //!< Flag for opening startup "new/open project" modal
    bool openSaveProjectModal_;               //!< Flag for opening "save before closing?" modal
    unsigned gameTick_;                       //!< The tick to show/start on in the preview window

    std::string projectName_;                 //!< The name of the game project
    std::string projectDirectory_;            //!< The directory of the game project

    std::string selectedScene_;               //!< The currently selected scene
    std::string selectedPool_;                //!< The currently selected pool in a scene
    std::string selectedStartingObject_;      //!< The currently selected starting object in a pool
    std::string selectedSpawnArchetype_;      //!< The currently selected spawn archetype in a pool

    static std::string editorSpace_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////