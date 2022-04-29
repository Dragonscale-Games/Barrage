/* ======================================================================== */
/*!
 * \file            main.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
   A sample file on how to use the rendering engine provided by Barrage.
 */
/* ======================================================================== */

/* ======================================================================== */
/* Includes */
/* ======================================================================== */
#include <Rendering/GfxManager2D.hpp>
#include <Rendering/WindowManager.hpp>

/****************************************************************************/
/*!
  \brief
    The entry point for testing graphics code.
*/
/****************************************************************************/
int main()
{
  // The windowing module.
  Barrage::WindowManager windowing;
  Barrage::WindowManager::WindowData settings = {};
  settings.decorated_ = true;
  settings.width_ = 1920;
  settings.height_ = 1080;
  settings.title_ = "Barrage";
  windowing.Initialize(settings);
  
  // Update the windowi while it's open.
  while(!glfwWindowShouldClose(windowing.GetInternalHandle())) 
  {
    glfwPollEvents();
  }
  
  windowing.Shutdown();
  return 0;
}