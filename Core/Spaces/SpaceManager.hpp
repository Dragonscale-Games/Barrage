/* ======================================================================== */
/*!
 * \file            SpaceManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages all game spaces.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpaceManager_BARRAGE_H
#define SpaceManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Space.hpp"

namespace Barrage
{
  //! Manages all existing spaces and allows creation of new spaces
  class SpaceManager
  {
    public:
      SpaceManager();

      void Update();

      void Draw();

      void AddSpace(const std::string& name, const Space& space);

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