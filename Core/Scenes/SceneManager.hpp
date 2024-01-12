/* ======================================================================== */
/*!
 * \file            SceneManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Manages all game scenes.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SceneManager_BARRAGE_H
#define SceneManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Scene.hpp"

namespace Barrage
{
  class SceneManager
  {
    public:
      SceneManager();

      void AddScene(const std::string& name, Scene&& scene);

      Scene* GetScene(const std::string& name);

    public:
      SceneMap scenes_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SceneManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////