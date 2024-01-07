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
  //! A collection of scenes and game objects
  class Space
  {
    public:
      Space();

      Space(const Space&) = delete;
      Space& operator=(const Space&) = delete;
      Space(Space&&) = delete;
      Space& operator=(Space&&) = delete;

      void Update();

      void Draw();

      ActionManager& GetActionManager();

      ObjectManager& GetObjectManager();

      Random& GetRNG();

      void SetScene(const std::string& name);

      void SetPaused(bool isPaused);

      void SetVisible(bool isVisible);

      void AllowSceneChangesDuringUpdate(bool allow);

      bool IsPaused() const;

      bool IsVisible() const;

    private:
      ActionManager actionManager_;
      ObjectManager objectManager_;
      Random rng_;
      bool paused_;
      bool visible_;
      bool allowSceneChangesDuringUpdate_;
      bool isUpdating_;
      std::string queuedScene_;
  };

  using SpaceMap = std::map<std::string, Space>;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Space_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////