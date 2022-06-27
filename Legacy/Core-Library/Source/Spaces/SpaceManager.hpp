/* ======================================================================== */
/*!
 * \file            SpaceManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages all existing spaces and allows creation of new spaces.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpaceManager_BARRAGE_H
#define SpaceManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Space.hpp"

#include <list>

namespace Barrage
{
  //! Maps space names to spaces
  typedef std::unordered_map<std::string, Space*> SpaceMap;
  
  //! An ordered list of space names
  typedef std::list<std::string> SpaceLinkedList;

  //! Manages all existing spaces and allows creation of new spaces
  class SpaceManager
	{
    public:   
      SpaceManager();

      ~SpaceManager();

      void AddSpace(const std::string name, const std::string scene);

    private:
      SpaceMap spaces_;
      SpaceLinkedList updateOrder_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpaceManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////