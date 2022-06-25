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
#include <algorithm>

namespace Barrage
{
  std::string FileManager::QueryContentPath()
  {
    static std::string relativeContentPath = "./Assets/";
    assert(!relativeContentPath.empty());
    return relativeContentPath;
  }

  std::string FileManager::QueryUserPath()
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
    DWORD userDirBufferSize = 4096;
    std::vector<TCHAR> userDirBuffer(userDirBufferSize);
    GetUserProfileDirectoryA(tokenHandle, NULL, &userDirBufferSize);
    // Resize the buffer and get the user directory for real.
    userDirBuffer.resize(userDirBufferSize);
    success = GetUserProfileDirectoryA(tokenHandle, userDirBuffer.data(), &userDirBufferSize);
    assert(success);
    // Replace all back slashes by forward slashes.
    std::replace(userDirBuffer.begin(), userDirBuffer.end(), '\\', '/');
    // Append an additional forward slash.
    size_t endPosSlash = std::find(userDirBuffer.begin(), userDirBuffer.end(), '\0') - userDirBuffer.begin();
    assert(endPosSlash < userDirBuffer.size() - 1);
    assert(userDirBuffer[endPosSlash + 1] == '\0');
    userDirBuffer[endPosSlash] = '/';
    // Create a string user this buffer.
    std::string stringifiedDir = userDirBuffer.data();
    assert(!stringifiedDir.empty());
    return stringifiedDir;
  }
}
