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
 * This file is for the windows-specific implementations.
 *
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include <stdafx.h>
#include <File/FileManager.hpp>
#include <UserEnv.h>
#include <cassert>
#include <vector>

namespace Barrage
{
  std::string FileManager::QueryContentPath()
  {
    // Get the process token so we can query the user directory.
    BOOL success = true;
    HANDLE tokenHandle = NULL;
    // Disable the unreferenced parameter warning for release builds.
    UNREFERENCED(success);
    success = OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &tokenHandle);
    // I am not sure if we can continue with the engine if *this* fails.
    assert(success);
    assert(tokenHandle);
    // Query for the size of the user directory.
    DWORD userDirBufferSize;
    std::vector<char> userDirBuffer;
    GetUserProfileDirectory(NULL, NULL, &userDirBufferSize);
    // Resize the buffer and get the user directory for real.
    userDirBuffer.resize(userDirBufferSize);
    success = GetUserProfileDirectory(tokenHandle, userDirBuffer.data(), &userDirBufferSize);
    assert(success);
    // Create a string user this buffer.
    return std::string(userDirBuffer.data());
  }

  std::string FileManager::QueryUserPath()
  {
    static std::string relativeContentPath = "Assets/";
    return relativeContentPath;
  }
}
