/* ========================================================================= */
/*!
 *
 * \file            File/FileManager.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used for loading resources from disk and
 * a manager that caches them while providing utility functions
 * to save/load them easier.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include <stdafx.h>
#include "FileManager.hpp"

namespace Barrage
{
  //  ===========================================================================
  // Resource
  //  ===========================================================================

  FileResource::FileResource()
  {
  }

  FileResource::FileResource(FileResource&& other) noexcept :
    path_(std::move(other.path_)), filename_(std::move(other.filename_))
  {
  }

  FileResource::FileResource(const std::string& path, const std::string& filename) :
    path_(path), filename_(filename)
  {
  }

  const std::string& FileResource::GetPath() const
  {
    return path_;
  }

  const std::string& FileResource::GetFileName() const
  {
    return filename_;
  }

  void FileResource::Load() noexcept(false)
  {
    Load(path_ + filename_);
  }

  void FileResource::Save() const noexcept(false)
  {
    Save(path_ + filename_);
  }

  bool FileResource::HasFilenameExtension() const
  {
    NO_IMPL();
    return false;
  }

  //  ===========================================================================
  // FileManager
  //  ===========================================================================

  void FileManager::Initialize(const std::string& userPathAppend)
  {
    contentPath_ = QueryContentPath();
    userPath_ = QueryUserPath() + userPathAppend;
  }

  void FileManager::Shutdown()
  {
    cachedResources_.clear();
  }

  void FileManager::Save(const FileResource& file) const
  {
    file.Save();
  }

  const std::string& FileManager::GetContentPath() const
  {
    return contentPath_;
  }

  const std::string& FileManager::GetUserPath() const
  {
    return userPath_;
  }

  std::string FileManager::QueryContentPath()
  {
    static std::string relativeContentPath = "./Assets/";
    assert(!relativeContentPath.empty());
    return relativeContentPath;
  }
}
