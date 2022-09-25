/* ======================================================================== */
/*!
 * \file            Space.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A space is a collection of scenes and game objects. Each space represents
   a unique simulation.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Space_BARRAGE_H
#define Space_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/ObjectManager.hpp>
#include <Scenes/Scene.hpp>

namespace Barrage
{
  
  //! Maps scene names to scenes
  typedef std::unordered_map<std::string, Scene*> SceneMap;
  
  //! A collection of scenes and game objects
  class Space
	{
    public:   
      Space();

      ~Space();

      void Update();

      void Draw();

      ObjectManager& GetObjectManager();

      void AddScene(const std::string& name, Scene* scene);

      void SetScene(const std::string name);

      void SetPaused(bool isPaused);

      bool IsPaused();

    private:
      ObjectManager objectManager_;
      SceneMap scenes_;
      bool paused_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Space_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////