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
#include <Rendering/GfxRenderer2D.hpp>
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
  windowing.ResizeToWindowed();
  settings = windowing.GetSettings();

  // The resources manager for the graphics system.
  Barrage::GfxManager2D manager;
  manager.Initialize(windowing);

  // The rendering modulde.
  Barrage::GfxRenderer2D renderer;
  renderer.Initialize(manager);
  renderer.SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
  renderer.SetViewportSpace(glm::vec2(settings.width_, settings.height_));
  
  // Update the windowi while it's open.
  while(!glfwWindowShouldClose(windowing.GetInternalHandle())) 
  {
    glfwPollEvents();
    renderer.RenderRequests();
    renderer.FlushRequests();
    glfwSwapBuffers(windowing.GetInternalHandle());
  }
  
  renderer.Shutdown();
  manager.CleanAllResources();
  windowing.Shutdown();
  return 0;
}