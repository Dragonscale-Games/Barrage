/* ========================================================================= */
/*!
 *
 * \file            ObjectSource.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface for loading Barrage objects.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include <stdafx.h>
#include "ObjectSource.hpp"

#include <fstream>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

namespace Barrage
{
  ObjectSource::ObjectSource(const std::string_view& path, const std::string_view& filename) :
    FileResource(path, filename)
  {
  }

  const rapidjson::Document& ObjectSource::GetDocument() const
  {
    return objectDoc_;
  }

  rapidjson::Document& ObjectSource::GetDocument()
  {
    return objectDoc_;
  }

  void ObjectSource::Load(const std::string& filepath)
  {
    NO_IMPL();
    UNREFERENCED(filepath);
  }

  void ObjectSource::Save(const std::string& filepath) const
  {
    // Create a JSON writer for our object document.
    std::ofstream objectFile(filepath);
    rapidjson::OStreamWrapper objectFileWrapper(objectFile);
    rapidjson::PrettyWriter writer(objectFileWrapper);
    // Write our JSON file using the stream.
    objectDoc_.Accept(writer);
  }
}
