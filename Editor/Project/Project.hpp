/* ======================================================================== */
/*!
 * \file            Project.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Class for Barrage Editor game projects.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Project_BARRAGE_H
#define Project_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Editor.hpp>

namespace Barrage
{
  //! Class for Barrage Editor game projects
  class Project
  {
    public:
      static void Save();

      static void Load();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Project_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////