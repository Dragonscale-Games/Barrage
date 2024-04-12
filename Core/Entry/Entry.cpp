/* ======================================================================== */
/*!
 * \file            Entry.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
     Contains the information needed to initialize a game.
 */
 /* ======================================================================== */

#include <Entry/Entry.hpp>

#include <cstdio>
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include <rapidjson/prettywriter.h>
#include "Serialization/Serializer.hpp"

namespace Barrage
{
  Entry::SpaceEntry::SpaceEntry() :
    name_("Invalid"),
    scene_("Invalid")
  {
  }

  Entry::SpaceEntry::SpaceEntry(const std::string& name, const std::string& scene) :
    name_(name),
    scene_(scene)
  {
  }

  void Entry::AddTexture(const std::string& textureName)
  {
    textures_.push_back(textureName);
  }

  void Entry::AddSpace(const SpaceEntry& space)
  {
    spaces_.push_back(space);
  }

  bool Entry::SaveToFile(const Entry& entry, const std::string& path)
  {
    FILE* outFile = nullptr;
    fopen_s(&outFile, path.c_str(), "wb");

    if (outFile == nullptr)
    {
      return false;
    }

    rttr::variant entryVariant = entry;
    rapidjson::Document d;
    rapidjson::Value entryObject = Serialize(entryVariant, d.GetAllocator());

    char* writeBuffer = new char[65536];
    rapidjson::FileWriteStream outStream(outFile, writeBuffer, sizeof(writeBuffer));

    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(outStream);
    entryObject.Accept(writer);

    delete[] writeBuffer;
    fclose(outFile);

    return true;
  }

  Entry Entry::LoadFromFile(const std::string& path)
  {
    FILE* inFile = nullptr;
    fopen_s(&inFile, path.c_str(), "rb");

    if (inFile == nullptr)
    {
      return Entry();
    }

    char* readBuffer = new char[65536];
    rapidjson::FileReadStream inStream(inFile, readBuffer, sizeof(readBuffer));

    rapidjson::Document document;
    rapidjson::ParseResult success = document.ParseStream(inStream);

    delete[] readBuffer;
    fclose(inFile);

    if (!success)
    {
      return Entry();
    }

    Entry newEntry;

    Deserialize(newEntry, document);

    return newEntry;
  }
}