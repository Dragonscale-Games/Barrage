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

#include <Actions/ActionManager.hpp>
#include <Objects/ObjectManager.hpp>
#include <Random/Random.hpp>
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

      ActionManager& GetActionManager();

      ObjectManager& GetObjectManager();

      Random& GetRNG();

      void AddScene(const std::string& name, Scene* scene);

      void SetScene(const std::string name);

      void SetPaused(bool isPaused);

      void SetVisible(bool isVisible);

      bool IsPaused() const;
      
      bool IsVisible() const;

    private:
      ActionManager actionManager_;
      ObjectManager objectManager_;
      Random rng_;
      SceneMap scenes_;
      bool paused_;
      bool visible_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Space_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////