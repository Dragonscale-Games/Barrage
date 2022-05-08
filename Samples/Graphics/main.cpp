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

Barrage::GfxManager2D::MeshID CreateSampleMesh(Barrage::GfxManager2D& manager);
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
  renderer.SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

  // Create the assets needed to render a scene.
  GfxManager2D::MeshID mesh = CreateSampleMesh(manager);
  GfxManager2D::ShaderID shader = CreateSampleShader(manager);
  // Create a render request for the renderer to draw this mesh.
  GfxRenderer2D::InstancedRequest renderRequest = {};
  renderRequest.resources_.mesh_ = mesh;
  renderRequest.resources_.shader_ = shader;

  glm::vec2 position(0.0f, 0.0f);
  glm::vec2 scale(150.0f);
  RADIAN rotation = 0.25f * (22.0f / 7.0f); // 0.0f;
  renderRequest.transform_.positions_ = &position;
  renderRequest.transform_.scales_ = &scale;
  renderRequest.transform_.rotations_ = &rotation;
  renderRequest.transform_.count_ = 1;
  
  // Add the render request to the renderer.
  renderer.AddRequest(renderRequest);
  
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
  }
  
  renderer.Shutdown();
  manager.CleanAllResources();
  windowing.Shutdown();
  return 0;
}

Barrage::GfxManager2D::MeshID CreateSampleMesh(Barrage::GfxManager2D& manager)
{
  using namespace Barrage;
  const std::vector<GfxManager2D::Vertex> vertices = {
    GfxManager2D::Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
    GfxManager2D::Vertex(glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
    GfxManager2D::Vertex(glm::vec2( 0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
    GfxManager2D::Vertex(glm::vec2( 0.5f,  -0.5f), glm::vec2(1.0f, 0.0f)),
  };
  const std::vector<GfxManager2D::Face> faces = {
    GfxManager2D::Face(0, 1, 2),
    GfxManager2D::Face(2, 3, 0),
  };
  GfxManager2D::MeshSpecs specs = {};
  specs.vertices_ = vertices;
  specs.faces_ = faces;

  return manager.CreateMesh(specs);
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
