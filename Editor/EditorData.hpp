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
#include <Scenes/Scene.hpp>
#include "Widgets/Modals/Rename/RenameModal.hpp"

namespace Barrage
{
  //! Editor data
  struct EditorData
  {
    EditorData();
    
    bool isRunning_;                          //!< Keeps track of whether the editor is running
    bool gamePlaying_;                        //!< Keeps track of whether the game is playing
    bool sceneIsDirty_;                       //!< Flag for when user changes something in current scene
    bool openComponentModal_;                 //!< Flag for when user opens the "add component" modal
    bool openComponentArrayModal_;            //!< Flag for when user opens the "add component array" modal
    bool openTagModal_;                       //!< Flag for when user opens the "add tag" modal
    bool openRenameModal_;                    //!< Flag for when user opens the "rename" modal
    bool openProjectModal_;                   //!< Flag for when user opens the "project" modal
    RenameCallback renameCallback_;           //!< Contains function to call when user renames something
    std::string projectName_;                 //!< The name of the game project
    std::string projectDirectory_;            //!< The directory of the game project
    std::string selectedSpace_;               //!< The currently selected space
    std::string selectedScene_;               //!< The currently selected scene
    std::string selectedPool_;                //!< The currently selected pool
    std::string selectedObject_;              //!< The currently selected object
    std::string_view selectedComponent_;      //!< The currently selected component
    std::string_view selectedComponentArray_; //!< The currently selected component array
    std::string_view selectedTag_;            //!< The currently selected tag
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////