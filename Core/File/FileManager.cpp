/* ========================================================================= */
/*!
 *
 * \file            FileManager.cpp
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

  Resource::Resource()
  {
  }

  Resource::Resource(const std::string& path, const std::string& filename) :
    path_(path), filename_(filename)
  {
  }

  void Resource::Load() noexcept(false)
  {
    Load(path_ + filename_);
  }

  void Resource::Save() noexcept(false)
  {
    Save(path_ + filename_);
  }

  bool Resource::HasFilenameExtension() const
  {
    NO_IMPL();
    return false;
  }

  //  ===========================================================================
  // FileManager
  //  ===========================================================================

  void FileManager::Initialize(const std::string& userPathAppend)
  {
    contentPath_ = GetContentPath();
    userPath_ = GetUserPath() + userPathAppend;
  }

  void FileManager::Shutdown()
  {
    cachedResources_.clear();
  }

  const std::string& FileManager::GetContentPath() const
  {
    return contentPath_;
  }

  const std::string& FileManager::GetUserPath() const
  {
    return userPath_;
  }
}
