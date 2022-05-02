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
  Barrage::WindowManager::WindowData settings = {};
  settings.decorated_ = true;
  settings.width_ = 1920;
  settings.height_ = 1080;
  settings.title_ = "Barrage - Graphics Sample";
  windowing.Initialize(settings);
  windowing.ResizeToWindowed();
  settings = windowing.GetSettings();

  // The resources manager for the graphics system.
  Barrage::GfxManager2D manager;
  manager.Initialize(windowing);

  // The rendering module.
  Barrage::GfxRenderer2D renderer;
  renderer.Initialize(manager);
  renderer.SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
  renderer.SetViewportSpace(glm::vec2(settings.width_, settings.height_));

  // Create the assets needed to render a scene.
  GfxManager2D::MeshID mesh = CreateSampleMesh(manager);
  GfxManager2D::ShaderID shader = CreateSampleShader(manager);
  // Create a render request for the renderer to draw this mesh.
  GfxRenderer2D::SingleRequest renderRequest = {};
  renderRequest.resources_.mesh_ = mesh;
  renderRequest.resources_.shader_ = shader;
  renderRequest.transform_.position_ = glm::vec2(0.0f);
  renderRequest.transform_.scale_ = glm::vec2(1.0f);
  renderRequest.transform_.rotation_ = 0.0f;
  // Add the render request to the renderer.
  renderer.AddRequest(renderRequest);
  
  // Update the window while it's open.
  while(!glfwWindowShouldClose(windowing.GetInternalHandle())) 
  {
    glfwPollEvents();
    // Note that you don't have to resubmit requests if
    // don't need to.
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
  std::vector<GfxManager2D::Vertex> vertices = {
    GfxManager2D::Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
    GfxManager2D::Vertex(glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
    GfxManager2D::Vertex(glm::vec2( 0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
    GfxManager2D::Vertex(glm::vec2( 0.5f,  -0.5f), glm::vec2(1.0f, 0.0f)),
  };
  std::vector<GfxManager2D::Face> faces = {
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
  specs.stageSources_[GfxManager2D::ShaderStage::VERTEX_SHAHDER] =
  "#version 330 core\n"
  "layout (location = 0) in vec2 position;\n"
  "void main(void)\n"
  "{\n"
  "gl_Position = vec4(position, 0.0, 1.0);\n"
  "}\n";
  // The source code for the pixel shader.
  specs.stageSources_[GfxManager2D::ShaderStage::PIXEL_SHADER] =
  "#version 330 core\n"
  "out vec4 color;\n"
  "void main(void)\n"
  "{\n"
  "color = vec4(vec3(1), 1);"
  "}\n";
  return manager.CreateShader(specs);
}