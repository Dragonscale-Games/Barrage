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
    Scene* nextScene_;                        //!< On a scene change, the new scene is temporarily held here
    std::string selectedSpace_;               //!< The currently selected space
    std::string selectedScene_;               //!< The currently selected scene
    std::string selectedPool_;                //!< The currently selected pool
    std::string selectedObject_;              //!< The currently selected object
    std::string_view selectedComponent_;      //!< The currently selected component
    std::string_view selectedComponentArray_; //!< The currently selected component array
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////