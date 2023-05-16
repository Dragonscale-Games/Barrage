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

namespace Barrage
{
  //! Maps space names to spaces
  typedef std::unordered_map<std::string, Space*> SpaceMap;
  
  //! Manages all existing spaces and allows creation of new spaces
  class SpaceManager
	{
    public:   
      SpaceManager();

      ~SpaceManager();

      void Update();

      void Draw();

      void AddSpace(const std::string& name, Space* space);
      
      Space* GetSpace(const std::string& name);

      void SetSpacePaused(const std::string& name, bool isPaused);

    private:
      SpaceMap spaces_;
      std::list<std::string> updateOrder_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpaceManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////