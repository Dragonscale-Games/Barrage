/* ======================================================================== */
/*!
 * \file            Game.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Standard game loop for Barrage Engine.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Game.hpp"

#include "Systems/Draw/DrawSystem.hpp"
#include "Objects/Components/ComponentFactory.hpp"
#include "Objects/Spawning/SpawnRuleFactory.hpp"
#include "Components/Sprite/Sprite.hpp"
#include "Components/CircleCollider/CircleCollider.hpp"
#include "Components/BoundaryBox/BoundaryBox.hpp"
#include "Components/Spawner/Spawner.hpp"
#include "ComponentArrays/Position/PositionArray.hpp"
#include "SpawnRules/Position/PositionRules.hpp"

#include <iostream>

namespace Barrage
{
  Game::Game() :
    engine_(),
    isRunning_(false)
  {
  }

  void Game::Run()
  {
    if (!isRunning_)
    {
      isRunning_ = true;

      Initialize();

      while (isRunning_)
      {
        Update();
      }

      Shutdown();

      isRunning_ = false;
    }
  }

  void Game::Initialize()
  {
    engine_.Initialize();

    engine_.Spaces().AddSpace("Test Space");
    Space& testSpace = *engine_.Spaces().GetSpace("Test Space");

    Scene testScene;

    engine_.Scenes().AddScene("Test Scene", std::move(testScene));
    testSpace.SetScene("Test Scene");
  }

  void Game::Update()
  {
    engine_.Frames().StartFrame();
    
    engine_.Input().Reset();
    engine_.Window().PollEvents();

    unsigned numTicks = engine_.Frames().ConsumeTicks();
    for (unsigned i = 0; i < numTicks; ++i)
    {
      engine_.Spaces().Update();
    }

    engine_.Graphics().GetFramebuffer().BindFramebuffer();
    engine_.Graphics().ClearBackground();
    engine_.Spaces().Draw();
    engine_.Graphics().GetFramebuffer().UnbindFramebuffer();
    engine_.Graphics().DrawFsq();
    engine_.Window().SwapBuffers();

    if (engine_.Window().IsClosed())
    {
      isRunning_ = false;
    }

    if (engine_.Input().KeyTriggered(GLFW_KEY_S))
    {
      Scene* testScene = engine_.Scenes().GetScene("Test Scene");

      if (testScene)
      {
        Scene::SaveToFile(*testScene, "test_scene_boogalizer_s.scene");
      }
    }

    if (engine_.Input().KeyTriggered(GLFW_KEY_P))
    {
      Scene* testScene = engine_.Scenes().GetScene("Test Scene");

      if (testScene)
      {
        Scene::SaveToFile(*testScene, "test_scene_boogalizer_p.scene");
      }
    }

    engine_.Frames().EndFrame(!engine_.Window().IsFocused());
  }

  void Game::Shutdown()
  {
    engine_.Shutdown();
  }
}