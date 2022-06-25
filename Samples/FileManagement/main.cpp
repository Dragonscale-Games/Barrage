/* ======================================================================== */
/*!
 * \file            main.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
   A sample file showing the features available for file management in
   Barrage.
 */
/* ======================================================================== */

/* ======================================================================== */
/* Includes */
/* ======================================================================== */

#include <stdafx.h>
#include <iostream>
#include <File/FileManager.hpp>

/****************************************************************************/
/*!
  \brief
    Runs a demo for getting standard directories in Barrage.
  \param manager
    The file manager used for the demo.
*/
/****************************************************************************/
void DirectoryDemo(Barrage::FileManager& manager);
/****************************************************************************/
/*!
  \brief
    The entry point for testing debug features.
*/
/****************************************************************************/
int main()
{
  using Barrage::FileManager;
  FileManager fileManager;
  fileManager.Initialize();
  // Run the demos!
  DirectoryDemo(fileManager);
  // Shut down the system and quit.
  fileManager.Shutdown();
  return 0;
}

void DirectoryDemo(Barrage::FileManager& manager)
{
  using Barrage::FileManager;
  std::cout << "User Path: " << manager.GetUserPath() << std::endl;
  std::cout << "Content Path: " << manager.GetContentPath() << std::endl;
}
