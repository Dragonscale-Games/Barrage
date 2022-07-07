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
#include "Source/GameStates/GS_DemoGame.hpp"
#include <Engine/Engine.hpp>

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

    engine_.GSM().SetGameState(GS_DemoGame());

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxRegistry2D& registry = engine_.Registry();
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
  }

  void Game::Update()
  {
    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

    engine_.Input().Update();

    //Barrage::TestRenderer::Instance().StartFrame();
    drawing.StartFrame();

    if (engine_.GSM().GameStateIsRunning())
      engine_.GSM().Update();
    else
      isRunning_ = false;

    //Barrage::TestRenderer::Instance().EndFrame();
    drawing.EndFrame();

    //if (Barrage::TestRenderer::Instance().WindowClosed())
    if(!windowing.IsOpen())
      isRunning_ = false;
  }

  void Game::Shutdown()
  {
    engine_.Instance->Shutdown();

    Barrage::Engine::Instance = nullptr;
  }
}