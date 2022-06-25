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
 * 
 * This file is for the linux-specific implementations.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include <File/FileManager.hpp>

namespace Barrage
{
  std::string FileManager::QueryContentPath()
  {
    return "";
  }

  std::string FileManager::QueryUserPath()
  {
    return "";
  }
}
