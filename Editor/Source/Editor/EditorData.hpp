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
    
    bool isRunning_; //!< Keeps track of whether the editor is running

    std::string_view selectedPool_;   //!< The currently selected pool
    std::string_view selectedObject_; //!< The currently selected object
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////