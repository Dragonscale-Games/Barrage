/* ======================================================================== */
/*!
 * \file            Scene.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a list of pools and game objects to spawn in a space.
 */
 /* ======================================================================== */

#include "Scene.hpp"
#include <cstdio>
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include <rapidjson/prettywriter.h>

namespace Barrage
{
  Scene::Scene(const std::string& name) :
    name_(name),
    poolArchetypes_()
  {
  }

  Scene::Scene(const rapidjson::Value& data) :
    name_("Unknown Scene"),
    poolArchetypes_()
  {
    if (!data.IsObject())
    {
      return;
    }
    
    if (data.HasMember("Name") && data["Name"].IsString())
    {
      name_ = data["Name"].GetString();
    }
    
    if (data.HasMember("Pools") && data["Pools"].IsArray())
    {
      DeserializePoolArchetypes(data["Pools"]);
    }
  }

  Scene::Scene(const Scene& other) :
    name_(other.name_),
    poolArchetypes_()
  {
    CopyPoolArchetypes(other.poolArchetypes_);
  }

  Scene& Scene::operator=(const Scene& other)
  {
    name_ = other.name_;
    CopyPoolArchetypes(other.poolArchetypes_);

    return *this;
  }

  Scene::~Scene()
  {
    DeletePoolArchetypes();
  }

  bool Scene::HasPool(const std::string& name)
  {
    return GetPoolArchetype(name) != nullptr;
  }

  const std::string& Scene::GetName()
  {
    return name_;
  }

  PoolArchetype* Scene::GetPoolArchetype(const std::string& name)
  {
    for (auto it = poolArchetypes_.begin(); it != poolArchetypes_.end(); ++it)
    {
      PoolArchetype* archetype = *it;

      if (archetype->GetName() == name)
      {
        return archetype;
      }
    }

    return nullptr;
  }

  const std::vector<PoolArchetype*>& Scene::GetPoolArchetypes()
  {
    return poolArchetypes_;
  }

  void Scene::AddPoolArchetype(PoolArchetype* archetype, unsigned* index)
  {
    if (archetype == nullptr || HasPool(archetype->GetName()))
    {
      delete archetype;
      return;
    }
    
    if (index && poolArchetypes_.size() > *index)
    {
      poolArchetypes_.insert(poolArchetypes_.begin() + *index, archetype);
    }
    else
    {
      poolArchetypes_.push_back(archetype);
    }
  }

  PoolArchetype* Scene::ExtractPoolArchetype(const std::string& name, unsigned* index)
  {
    for (auto it = poolArchetypes_.begin(); it != poolArchetypes_.end(); ++it)
    {
      PoolArchetype* archetype = *it;

      if (archetype->GetName() == name)
      {
        if (index)
        {
          *index = static_cast<unsigned>(it - poolArchetypes_.begin());
        }

        poolArchetypes_.erase(it);

        return archetype;
      }
    }
    
    return nullptr;
  }

  rapidjson::Value Scene::Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value sceneObject;
    sceneObject.SetObject();

    rapidjson::Value nameValue(name_.c_str(), static_cast<rapidjson::SizeType>(name_.size()), allocator);
    sceneObject.AddMember("Name", nameValue, allocator);

    rapidjson::Value poolArchetypesObject = SerializePoolArchetypes(allocator);
    sceneObject.AddMember("Pools", poolArchetypesObject, allocator);

    return sceneObject;
  }

  bool Scene::SaveToFile(Scene* scene, const std::string& path)
  {
    FILE* outFile = nullptr;
    fopen_s(&outFile, path.c_str(), "wb");

    if (outFile == nullptr)
    {
      return false;
    }

    rapidjson::Document d;
    rapidjson::Value sceneObject = scene->Serialize(d.GetAllocator());

    char* writeBuffer = new char[65536];
    rapidjson::FileWriteStream outStream(outFile, writeBuffer, sizeof(writeBuffer));

    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(outStream);
    sceneObject.Accept(writer);

    delete[] writeBuffer;
    fclose(outFile);

    return true;
  }

  Scene* Scene::LoadFromFile(const std::string& path)
  {
    FILE* inFile = nullptr;
    fopen_s(&inFile, path.c_str(), "rb");

    if (inFile == nullptr)
    {
      return nullptr;
    }

    char* readBuffer = new char[65536];
    rapidjson::FileReadStream inStream(inFile, readBuffer, sizeof(readBuffer));

    rapidjson::Document document;
    rapidjson::ParseResult success = document.ParseStream(inStream);

    delete[] readBuffer;
    fclose(inFile);

    if (!success)
    {
      return nullptr;
    }

    Scene* scene = new Scene(document);

    return scene;
  }

  void Scene::CopyPoolArchetypes(const std::vector<PoolArchetype*>& other)
  {
    DeletePoolArchetypes();

    for (auto it = other.begin(); it != other.end(); ++it)
    {
      poolArchetypes_.push_back(new PoolArchetype(**it));
    }
  }

  void Scene::DeletePoolArchetypes()
  {
    for (auto it = poolArchetypes_.begin(); it != poolArchetypes_.end(); ++it)
    {
      delete* it;
    }

    poolArchetypes_.clear();
  }

  rapidjson::Value Scene::SerializePoolArchetypes(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator)
  {
    rapidjson::Value poolArchetypeArray;
    poolArchetypeArray.SetArray();

    for (auto it = poolArchetypes_.begin(); it != poolArchetypes_.end(); ++it)
    {
      PoolArchetype* archetype = *it;
      rapidjson::Value archetypeObject = archetype->Serialize(allocator);
      poolArchetypeArray.PushBack(archetypeObject, allocator);
    }

    return poolArchetypeArray;
  }

  void Scene::DeserializePoolArchetypes(const rapidjson::Value& data)
  {
    for (auto it = data.Begin(); it != data.End(); ++it)
    {
      if (it->IsObject())
      {
        PoolArchetype* poolArchetype = new PoolArchetype(*it);
        AddPoolArchetype(poolArchetype);
      }
    }
  }
}