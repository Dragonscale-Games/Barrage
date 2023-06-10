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

#include "Game.hpp"

#include <cstdio>
#include "rapidjson/filereadstream.h"
#include <iostream>

namespace Barrage
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
    engine_.Initialize();

    Barrage::WindowManager& windowing = engine_.Windowing();
    Barrage::GfxDraw2D& drawing = engine_.Drawing();

    // Set the viewport of our game.
    const Barrage::WindowManager::WindowData& settings = windowing.GetSettings();
    drawing.SetViewportSpace(glm::ivec2(settings.width_, settings.height_));

    float zoom = 1.0f;
    float angle = 0.0f;
    glm::vec2 position(0.0f);

    engine_.Drawing().SetCameraTransform(position, zoom, angle);

    ParseEntryFile();
    
    std::vector<std::string> spaceNames = engine_.Spaces().GetSpaceNames();

    for (auto it = spaceNames.begin(); it != spaceNames.end(); ++it)
    {
      std::cout << "Found space: " << *it << std::endl;
    }

    if (spaceNames.empty())
    {
      std::cout << "No spaces found." << std::endl;
    }
  }

  void Game::Update()
  {
    engine_.Frames().StartFrame();

    engine_.Input().Update();

    unsigned num_ticks = engine_.Frames().ConsumeTicks();
    for (unsigned i = 0; i < num_ticks; ++i)
    {
      engine_.Spaces().Update();
    }

    engine_.Drawing().StartFrame();
    engine_.Spaces().Draw();
    engine_.Drawing().EndFrame();

    if (!engine_.Windowing().IsOpen())
    {
      isRunning_ = false;
    }

    engine_.Frames().EndFrame();
  }

  void Game::Shutdown()
  {
    engine_.Shutdown();
  }

  void Game::ParseEntryFile()
  {
    FILE* inFile = nullptr;
    fopen_s(&inFile, "./Assets/entry.json", "rb");
    
    if (inFile == nullptr)
    {
      return;
    }
    
    char* readBuffer = new char[65536];
    rapidjson::FileReadStream inStream(inFile, readBuffer, sizeof(readBuffer));
    
    rapidjson::Document document;
    rapidjson::ParseResult success = document.ParseStream(inStream);
    
    delete[] readBuffer;
    fclose(inFile);
    
    if (!success)
    {
      return;
    }

    if (!document.IsObject())
    {
      return;
    }

    if (document.HasMember("Spaces") && document["Spaces"].IsArray())
    {
      for (auto it = document["Spaces"].Begin(); it != document["Spaces"].End(); ++it)
      {
        if (it->IsString())
        {
          Space* new_space = new Space;
          engine_.Spaces().AddSpace(it->GetString(), new_space);
        }
      }
    }
  }
}