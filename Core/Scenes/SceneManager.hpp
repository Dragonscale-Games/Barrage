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
#include <unordered_map>

namespace Barrage
{
  //! Maps scene names to scenes
  typedef std::unordered_map<std::string, Scene*> SceneMap;

  //! Manages all existing spaces and allows creation of new spaces
  class SceneManager
  {
    public:
      SceneManager();

      ~SceneManager();

      void AddScene(Scene* scene);

      Scene* GetScene(const std::string& name);

      std::vector<std::string> GetSceneNames();

      bool RenameScene(const std::string& sceneName, const std::string& newName);

      void Clear();

    private:
      SceneMap scenes_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SceneManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////