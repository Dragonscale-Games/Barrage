/* ======================================================================== */
/*!
 * \file            DemoGame.hpp
 * \par             Demo Game
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A simple game environment using Barrage Engine.
 */
 /* ======================================================================== */

#include "DemoGame.hpp"
#include "../Initialization/DemoInitialization.hpp"
#include <Engine/Engine.hpp>
#include <iostream>

namespace Demo
{
  Game::Game() :
    engine_(),
    isRunning_()
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
    Barrage::Engine::Instance = &engine_;

    engine_.Initialize();

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxRegistry2D& registry = engine_.GfxRegistry();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();
    // Register the assets necessary.
    const char* instancedShaderPaths[] = {
      "Assets/Shaders/Default/Instanced.vs",
      "Assets/Shaders/Default/Instanced.fs",
    };
    registry.RegisterShader(instancedShaderPaths, "Instanced");
    registry.RegisterTexture("Assets/Textures/TestBullet.png", "TestBullet");
    registry.RegisterTexture("Assets/Textures/TestShip.png", "TestShip");
    // Set any default resources on the draw system.
    drawing.ApplyShader("Instanced");
    // Set the viewport of our game.
    const Barrage::WindowManager::WindowData& settings = windowing.GetSettings();
    drawing.SetViewportSpace(glm::ivec2(settings.width_, settings.height_));

    Barrage::Space* demo_space = CreateDemoSpace();
    engine_.Spaces().AddSpace("Demo Space", demo_space);

    float zoom = 1.0f;
    float angle = 0.0f;
    glm::vec2 position(0.0f);

    engine_.Drawing().SetCameraTransform(position, zoom, angle);
  }

  void Game::Update()
  {
    engine_.Frames().StartFrame();
    
    engine_.Input().Update();

    TimePoint beginT;
    TimePoint endT;

    unsigned num_ticks = engine_.Frames().ConsumeTicks();
    for (unsigned i = 0; i < num_ticks; ++i)
    {
      beginT = std::chrono::high_resolution_clock::now();
      engine_.Spaces().Update();
      endT = std::chrono::high_resolution_clock::now();
    }

    if (num_ticks)
    {
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endT - beginT);
      std::cout << "Frame time (microseconds): " << duration.count() << std::endl;
    }

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

    drawing.StartFrame();
    engine_.Spaces().Draw();
    drawing.EndFrame();

    if(!windowing.IsOpen())
    {
      isRunning_ = false;
    }
      
    engine_.Frames().EndFrame();
  }

  void Game::Shutdown()
  {
    engine_.Shutdown();

    Barrage::Engine::Instance = nullptr;
  }
}