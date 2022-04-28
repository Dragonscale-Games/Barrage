/* ======================================================================== */
/*!
 * \file            GSBaldeon.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
/* ======================================================================== */

#include "GSBaldeon.hpp"
#include "GameStates/GSEntry.hpp"

#include <Engine/Engine.hpp>
#include <stb_image/stb_image.h>

namespace Barrage
{
  static GfxManager2D::MeshID mesh;
  static GfxManager2D::TextureID texture;
  static GfxManager2D::ShaderID shader;

  static GfxManager2D::TextureID LoadImage(GfxManager2D& gfxManager, const std::string& filepath)
  {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(filepath.c_str(), &width, &height, &channels, 4);

    GfxManager2D::TextureSpecs textureSpecs = { 0 };
    textureSpecs.createMipmaps_ = true;
    textureSpecs.dimensions_ = 2;
    textureSpecs.format_ = GfxManager2D::R8G8B8A8;
    textureSpecs.width_ = width;
    textureSpecs.height_ = height;
    textureSpecs.pixels_ = reinterpret_cast<const unsigned char* const>(pixels);

    GfxManager2D::TextureID newTexture = gfxManager.CreateTexture(textureSpecs);
    stbi_image_free(pixels);

    return newTexture;
  }

  GSBaldeon::GSBaldeon() : GameState(Enter, Update, Exit)
  {
  }

  void GSBaldeon::Enter()
  {
    // The graphics manager to get the resources from.
    GfxManager2D& gfxManager = Engine::GfxManager();

    // The vertices for the mesh.
    std::vector<GfxManager2D::Vertex> vertices;
    vertices.reserve(4);
    vertices.push_back(GfxManager2D::Vertex(glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f)));
    vertices.push_back(GfxManager2D::Vertex(glm::vec2(-0.5f, 0.5f), glm::vec2(0.0f, 1.0f)));
    vertices.push_back(GfxManager2D::Vertex(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 1.0f)));
    vertices.push_back(GfxManager2D::Vertex(glm::vec2(0.5f, -0.5f), glm::vec2(1.0f, 0.0f)));
    // The faces of said mesh.
    std::vector<GfxManager2D::Face> faces;
    faces.reserve(2);
    faces.push_back(GfxManager2D::Face(0, 1, 2));
    faces.push_back(GfxManager2D::Face(2, 3, 0));
    // Specify the mesh being used.
    GfxManager2D::MeshSpecs meshSpecs;
    meshSpecs.vertices_ = vertices;
    meshSpecs.faces_ = faces;

    // Create the handle to the mesh.
    mesh = gfxManager.CreateMesh(meshSpecs);

    // The shader code for the vertex fragment
    const char* const vertexCode =
      "#version 330 core\n"                                                                 \
      "layout (location = 0) in vec2 position;\n"                                           \
      "layout (location = 1) in vec2 uvCoordinate;\n"                                       \
      "out vec2 uv;\n"                                                                      \
      "uniform vec2 translation;\n"                                                         \
      "uniform vec2 scale;\n"                                                               \
      "uniform float rotation;\n"                                                           \
      "void main(void) {\n"                                                                 \
      "mat3 transform;\n"                                                                   \
      "transform[0] = vec3(scale.x * cos(rotation), scale.y * sin(rotation), 0.0f);\n"      \
      "transform[1] = vec3(-scale.x * sin(rotation), scale.y * cos(rotation), 0.0f);\n"     \
      "transform[2] = vec3(translation.x, translation.y, 1.0f);\n"                          \
      "gl_Position = vec4(transform * vec3(position, 1.0f), 1.0);\n"                        \
      "uv = uvCoordinate;\n"                                                                \
      "}"                                                                                   \
      ;
    // The shader code for the pixel fragment
    const char* const pixelCode =
      "#version 330 core\n"                                                 \
      "in vec2 uv;\n"                                                       \
      "out vec4 color;\n"                                                   \
      "uniform sampler2D diffuse;\n"                                        \
      "void main(void) {\n"                                                 \
      "color = texture(diffuse, uv);\n"                                     \
      "}"                                                                   \
      ;
    // Get the shader id from the graphics manager.
    GfxManager2D::ShaderSpecs shaderSpecs;
    shaderSpecs.stageSources_[GfxManager2D::VERTEX_SHAHDER] = vertexCode;
    shaderSpecs.stageSources_[GfxManager2D::PIXEL_SHADER] = pixelCode;
    shader = gfxManager.CreateShader(shaderSpecs);

    texture = LoadImage(gfxManager, "Assets\\Textures\\MC-Concept-1.jpg");
  }

  void GSBaldeon::Update()
  {
    if (Engine::Input().KeyTriggered(KEY_BACKSPACE))
    {
      Engine::GSM().SetGameState(GSEntry());
    }

    GfxManager2D& gfxManager = Engine::GfxManager();
    GfxRenderer2D& gfxRenderer = Engine::GfxRenderer();
    GfxRenderer2D::SingleRequest request;
    request.resources_.mesh_ = mesh;
    request.resources_.shader_ = shader;
    request.resources_.texture_ = texture;

    request.transform_.position_ = glm::vec2(0.0f);
    request.transform_.scale_ = glm::vec2(1.0f, 1.2898f);
    request.transform_.rotation_ = 0.0f;

    gfxRenderer.SetViewportSpace(glm::vec2(1920, 1080));
    gfxRenderer.AddRequest(request);
    gfxRenderer.RenderRequests();
    gfxRenderer.FlushRequests();
  }

  void GSBaldeon::Exit()
  {

  }
}