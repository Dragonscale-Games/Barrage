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

#include <Rendering/GfxPrimitives.hpp>
#include <Rendering/GfxManager2D.hpp>
#include <Rendering/GfxRenderer2D.hpp>
#include <Rendering/GfxDraw2D.hpp>
#include <Rendering/GfxFactory2D.hpp>

#include <Rendering/WindowManager.hpp>


Barrage::GfxManager2D::ShaderID CreateSampleShader(Barrage::GfxManager2D& manager);

/****************************************************************************/
/*!
  \brief
    The entry point for testing graphics code.
*/
/****************************************************************************/
int main()
{
  using namespace Barrage;
  
  // The windowing module.
  Barrage::WindowManager windowing;
  Barrage::WindowManager::WindowData initSettings = {};
  initSettings.decorated_ = true;
  initSettings.width_ = 1920;
  initSettings.height_ = 1080;
  initSettings.title_ = "Barrage - Graphics Sample";
  windowing.Initialize(initSettings);
  windowing.ResizeToWindowed();
  initSettings = windowing.GetSettings();

  // The resources manager for the graphics system.
  Barrage::GfxManager2D manager;
  manager.Initialize(windowing);
  // The rendering module.
  Barrage::GfxRenderer2D renderer;
  renderer.Initialize(manager);
  renderer.SetBackgroundColor(glm::vec4(0.2f, 0.1f, 0.1f, 1.0f));
  // The drawing module that simplifies rendering.
  Barrage::GfxDraw2D drawing;
  drawing.Initialize(manager, renderer);
  // The factory module that lets the user create
  // resources for the graphics modules from files.
  Barrage::GfxFactory2D factory;
  factory.Initialize(manager);

  // Create the assets needed to render a scene.
  // Attempt to create our shaders from files.
  std::array<const char*, GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE> filepaths = {
    "instanced.vs", "instanced.fs"
  };
  GfxManager2D::ShaderID shader = factory.CreateShader(filepaths.data());
  if(shader == -1)
  {
    shader = CreateSampleShader(manager);
  }
  
  drawing.ApplyShader(shader);
  // Tell the drawing system to draw a couple of squares on the screen.
  constexpr int size = 2;
  glm::vec2 positions[size] = { glm::vec2(-150.0f, 0.0f), glm::vec2(150.0f, 0.0f) };
  glm::vec2 scales[size] = { glm::vec2(150.0f), glm::vec2(50.0f, 120.0f) };
  RADIAN rotations[size] = { 0.25f * (22.0f / 7.0f), 0.0f };
  drawing.DrawInstancedQuad(size, positions, scales, rotations);
  
  // Update the window while it's open.
  while(!glfwWindowShouldClose(windowing.GetInternalHandle())) 
  {
    glfwPollEvents();
    // Note that you don't have to resubmit requests if
    // don't need to.
    const WindowManager::WindowData& settings = windowing.GetSettings();
    const glm::vec2 dimensions(settings.width_, settings.height_);
    renderer.SetViewportSpace(dimensions);
    renderer.RenderRequests();
    glfwSwapBuffers(windowing.GetInternalHandle());
    glfwSwapInterval(1);
  }
  
  renderer.Shutdown();
  manager.CleanAllResources();
  windowing.Shutdown();
  return 0;
}

Barrage::GfxManager2D::ShaderID CreateSampleShader(Barrage::GfxManager2D& manager)
{
  using namespace Barrage;
  GfxManager2D::ShaderSpecs specs = {};
  // The source code for the vertex shader.
  specs.stageSources_[GfxManager2D::ShaderStage::VERTEX_SHADER] =
  "#version 330 core\n"
  "layout (location = 0) in vec2 vertex;\n"
  "layout (location = 2) in vec2 position;\n"
  "layout (location = 3) in vec2 scale;\n"
  "layout (location = 4) in float rotation;\n"
  "uniform mat4 projection;\n"
  "void main(void)\n"
  "{\n"
  "  vec2 v = scale * vertex;"
  "  v = vec2( v.x * cos(rotation) - v.y * sin(rotation), v.x * sin(rotation) + v.y * cos(rotation) );\n"
  "  v += position;"
  "  gl_Position = projection * vec4(v, 0.0, 1.0);\n"
  "}\n";
  // The source code for the pixel shader.
  specs.stageSources_[GfxManager2D::ShaderStage::PIXEL_SHADER] =
  "#version 330 core\n"
  "out vec4 color;\n"
  "void main(void)\n"
  "{\n"
  "  color = vec4(vec3(1), 1);\n"
  "}\n";
  return manager.CreateShader(specs);
}
