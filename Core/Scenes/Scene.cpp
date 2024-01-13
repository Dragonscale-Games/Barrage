/* ======================================================================== */
/*!
 * \file            Scene.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a list of pools (and their objects) to spawn in a space.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "Scene.hpp"

#include <cstdio>
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include <rapidjson/prettywriter.h>
#include "Serialization/Serializer.hpp"

namespace Barrage
{
  Scene::Scene() :
    name_("<untitled>"),
    poolArchetypes_()
  {
  }
  
  Scene::Scene(const std::string& name) :
    name_(name),
    poolArchetypes_()
  {
  }

  void Scene::SetName(const std::string& name)
  {
    name_ = name;
  }

  const std::string& Scene::GetName()
  {
    return name_;
  }

  const PoolArchetypeMap& Scene::GetPoolArchetypes()
  {
    return poolArchetypes_;
  }

  bool Scene::SaveToFile(const Scene& scene, const std::string& path)
  {
    FILE* outFile = nullptr;
    fopen_s(&outFile, path.c_str(), "wb");

    if (outFile == nullptr)
    {
      return false;
    }

    rttr::variant sceneVariant = scene;
    rapidjson::Document d;
    rapidjson::Value sceneObject = Serialize(sceneVariant, d.GetAllocator());

    char* writeBuffer = new char[65536];
    rapidjson::FileWriteStream outStream(outFile, writeBuffer, sizeof(writeBuffer));

    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(outStream);
    sceneObject.Accept(writer);

    delete[] writeBuffer;
    fclose(outFile);

    return true;
  }

  Scene Scene::LoadFromFile(const std::string& path)
  {
    FILE* inFile = nullptr;
    fopen_s(&inFile, path.c_str(), "rb");

    if (inFile == nullptr)
    {
      return Scene();
    }

    char* readBuffer = new char[65536];
    rapidjson::FileReadStream inStream(inFile, readBuffer, sizeof(readBuffer));

    rapidjson::Document document;
    rapidjson::ParseResult success = document.ParseStream(inStream);

    delete[] readBuffer;
    fclose(inFile);

    if (!success)
    {
      return Scene();
    }

    Scene newScene;

    Deserialize(newScene, document);

    return newScene;
  }
}