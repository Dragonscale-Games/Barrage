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

    PoolArchetype spawnerPoolArchetype("Spawner Pool");

    spawnerPoolArchetype.components_.emplace("Spawner", ComponentFactory::AllocateComponent("Spawner"));
    Spawner& spawner = dynamic_cast<SpawnerComponent&>(*spawnerPoolArchetype.components_.at("Spawner")).Data();

    SpawnLayer spawnLayer0;

    GenericSpawnRule randomOffsetRule0 = SpawnRuleFactory::CreateSpawnRule("RandomOffset");

    Spawn::RandomOffsetData randomOffsetData0;

    randomOffsetData0.xVariance_ = 50.0f;
    randomOffsetData0.yVariance_ = 50.0f;

    rttr::variant randomOffset0Value = randomOffsetData0;

    randomOffsetRule0->SetRTTRValue(randomOffset0Value);

    spawnLayer0.baseNumGroups_ = 10;

    spawnLayer0.valueRules_.AddSpawnRule(SpawnRuleFactory::CreateSpawnRule("MatchPosition"));
    spawnLayer0.valueRules_.AddSpawnRule(randomOffsetRule0);
    
    SpawnLayer spawnLayer1;

    GenericSpawnRule randomOffsetRule1 = SpawnRuleFactory::CreateSpawnRule("RandomOffset");

    Spawn::RandomOffsetData randomOffsetData1;

    randomOffsetData1.xVariance_ = 960.0f;
    randomOffsetData1.yVariance_ = 540.0f;

    rttr::variant randomOffset1Value = randomOffsetData1;

    randomOffsetRule1->SetRTTRValue(randomOffset1Value);

    spawnLayer1.baseNumGroups_ = 5;
    spawnLayer1.valueRules_.AddSpawnRule(randomOffsetRule1);

    SpawnType spawnType;

    spawnType.destinationPool_ = "Bullet Pool";
    spawnType.spawnArchetype_ = "Bullet Object";
    spawnType.spawnLayers_.push_back(spawnLayer0);
    spawnType.spawnLayers_.push_back(spawnLayer1);

    AutomaticSpawn automaticSpawn;

    automaticSpawn.delay_ = 0;
    automaticSpawn.spawnType_ = "Test Spawn Type";
    automaticSpawn.ticksPerSpawn_ = 10;

    SpawnPattern pattern;

    pattern.automaticSpawns_.push_back(automaticSpawn);

    spawner.patterns_.emplace("Test Pattern", pattern);
    spawner.currentPattern_ = "Test Pattern";
    spawner.spawnTypes_.emplace("Test Spawn Type", spawnType);

    spawnerPoolArchetype.componentArrayNames_.insert("Position");
    spawnerPoolArchetype.componentArrayNames_.insert("SpawnTimer");

    ObjectArchetype spawnerObjectArchetype("Spawner Object", spawnerPoolArchetype.componentArrayNames_);

    spawnerPoolArchetype.startingObjects_.emplace("Spawner Object", spawnerObjectArchetype);

    PoolArchetype bulletPoolArchetype("Bullet Pool", 100000);

    bulletPoolArchetype.components_.emplace("Sprite", ComponentFactory::AllocateComponent("Sprite"));

    bulletPoolArchetype.componentArrayNames_.insert("ColorTint");
    bulletPoolArchetype.componentArrayNames_.insert("Position");
    bulletPoolArchetype.componentArrayNames_.insert("Rotation");
    bulletPoolArchetype.componentArrayNames_.insert("Scale");
    bulletPoolArchetype.componentArrayNames_.insert("TextureUV");

    ObjectArchetype bulletObjectArchetype("Bullet Object", bulletPoolArchetype.componentArrayNames_);

    bulletPoolArchetype.spawnArchetypes_.emplace("Bullet Object", bulletObjectArchetype);

    Scene testScene("Test Scene");

    testScene.poolArchetypes_.emplace("Bullet Pool", bulletPoolArchetype);
    testScene.poolArchetypes_.emplace("Spawner Pool", spawnerPoolArchetype);

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

    engine_.Frames().EndFrame(!engine_.Window().IsFocused());
  }

  void Game::Shutdown()
  {
    engine_.Shutdown();
  }
}