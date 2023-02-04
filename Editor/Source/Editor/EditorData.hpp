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
    
    std::string_view selectedPool_;          //!< The currently selected pool
    std::string_view selectedPoolArchetype_; //!< The currently selected pool archetype
    std::string_view selectedObject_;        //!< The currently selected object
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditorData_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////