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

    engine_.Graphics().StartFrame();
    engine_.Graphics().StartFramebufferRendering();
    engine_.Spaces().Draw();
    engine_.Graphics().EndFramebufferRendering();
    engine_.Graphics().DrawFSQ();
    engine_.Graphics().EndFrame();

    if (engine_.Graphics().WindowClosed())
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

    /*if (document.HasMember("Textures") && document["Textures"].IsArray())
    {
      for (auto it = document["Textures"].Begin(); it != document["Textures"].End(); ++it)
      {
        if (it->IsString())
        {
          std::string texture_name = it->GetString();
          std::string texture_path = "Assets/Textures/" + texture_name + ".png";
          engine_.GfxRegistry().RegisterTexture(texture_path.c_str(), texture_name.c_str());
        }
      }
    }*/

    if (document.HasMember("Spaces") && document["Spaces"].IsArray())
    {
      for (auto it = document["Spaces"].Begin(); it != document["Spaces"].End(); ++it)
      {
        const rapidjson::Value& space_object = *it;
        
        if (space_object.IsObject() && space_object.HasMember("Name") && space_object["Name"].IsString())
        {
          Space* new_space = new Space;

          if (space_object.HasMember("Scene") && space_object["Scene"].IsString())
          {
            std::string scene_name = space_object["Scene"].GetString();
            std::string path = "./Assets/Scenes/" + scene_name + ".scene";

            Scene* new_scene = Scene::LoadFromFile(path);

            if (new_scene)
            {
              engine_.Scenes().AddScene(new_scene);
              new_space->SetScene(scene_name);
            }
          }

          engine_.Spaces().AddSpace(space_object["Name"].GetString(), new_space);
        }
      }
    }
  }
}