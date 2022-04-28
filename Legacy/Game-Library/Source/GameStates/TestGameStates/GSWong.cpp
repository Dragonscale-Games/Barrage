/* ======================================================================== */
/*!
 * \file            GSWong.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>

 */
/* ======================================================================== */

#include "GSWong.hpp"
#include "GameStates/GSEntry.hpp"

#include <stb_image/stb_image.h>

#include <Engine/Engine.hpp>
#include <Rendering/GfxManager2D.hpp>
#include <Rendering/GfxRenderer2D.hpp>
#include <Rendering/WindowManager.hpp>

namespace Barrage
{
  static const int numInstances = 36;
  static glm::vec2 instancedTranslations[numInstances];
  static glm::vec2 instancedScales[numInstances];
  static float instancedRotations[numInstances] = { 0.0f };
  static float rotation;

  static GfxManager2D::MeshID mesh;

  static GfxManager2D::TextureID texture;
  static GfxManager2D::TextureID instancedTexture;

  static GfxManager2D::ShaderID shader;
  static GfxManager2D::ShaderID instancedShader;

  static GfxManager2D::TextureID GenerateTexture(GfxManager2D& gfxManager, unsigned int color1, unsigned int color2)
  {
    const unsigned int pixels[] = {
      color1, color2, color1,
      color2, color1, color2,
      color1, color2, color1,
    };
    const int width = 3, height = 3;
    // Create the specifications for the texure.
    GfxManager2D::TextureSpecs textureSpecs = { 0 };
    textureSpecs.createMipmaps_ = true;
    textureSpecs.dimensions_ = 2;
    textureSpecs.format_ = GfxManager2D::R8G8B8A8;
    textureSpecs.width_ = width;
    textureSpecs.height_ = height;
    textureSpecs.pixels_ = reinterpret_cast<const unsigned char* const>(pixels);
    // Get the ID for the texture created.
    return gfxManager.CreateTexture(textureSpecs);
  }

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

  GSWong::GSWong() : GameState(Enter, Update, Exit)
  {
  }

  void GSWong::Enter()
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
    const char* const instancedVertexCode =
      "#version 330 core\n"                                                                 \
      "layout (location = 0) in vec2 position;\n"                                           \
      "layout (location = 1) in vec2 uvCoordinate;\n"                                       \
      "layout (location = 2) in vec2 translation;\n"                                        \
      "layout (location = 3) in vec2 scale;\n"                                              \
      "layout (location = 4) in float rotation;\n"                                          \
      "out vec2 uv;\n"                                                                      \
      "uniform mat4 projection;\n"                                                          \
      "void main(void) {\n"                                                                 \
      "mat3 transform;\n"                                                                   \
      "transform[0] = vec3(scale.x * cos(rotation), scale.y * sin(rotation), 0.0f);\n"      \
      "transform[1] = vec3(-scale.x * sin(rotation), scale.y * cos(rotation), 0.0f);\n"     \
      "transform[2] = vec3(translation.x, translation.y, 1.0f);\n"                          \
      "gl_Position = projection * vec4(transform * vec3(position, 1.0f), 1.0);\n"           \
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

    shaderSpecs.stageSources_[GfxManager2D::VERTEX_SHAHDER] = instancedVertexCode;
    instancedShader = gfxManager.CreateShader(shaderSpecs);

    instancedTexture = GenerateTexture(gfxManager, 0xFFAAAAAA, 0xFFFFFFFF);
    texture = LoadImage(gfxManager, "Assets\\Textures\\MC-Concept-1.jpg");

    // Reset transform stats.
    rotation = 0.0f;

    const float a = -500.0f;
    const float b = 500.0f;
    for (int i = 0; i < numInstances; ++i)
    {
      const float t = static_cast<float>(i) / static_cast<float>(numInstances);
      instancedTranslations[i] = glm::vec2(a + (b - a) * t, 0.0f);
    }
    std::fill(instancedScales, instancedScales + numInstances, glm::vec2(100.0f));
}

  void GSWong::Update()
  {
    // The graphics manager to get the resources from.
    GfxManager2D& gfxManager = Engine::GfxManager();
    // The graphics renderer.
    GfxRenderer2D& gfxRenderer = Engine::GfxRenderer();

    if (Engine::Input().KeyTriggered(KEY_BACKSPACE))
    {
      Engine::GSM().SetGameState(GSEntry());
    }

    // Increase the rotation.
    const float pi = 22.0f / 7.0f;
    rotation += 1.0f / 60.0f;

    for (int i = 0; i < numInstances; ++i)
    {
      instancedRotations[i] = static_cast<float>(i + 1) * rotation / 2.0f;
      if (i % 2 == 0)
      {
        instancedRotations[i] *= 1.0f;
      }
    }

    // Fill out two single request for the two squares.
    GfxRenderer2D::SingleRequest request;
    request.resources_.mesh_ = mesh;
    request.resources_.shader_ = shader;
    request.resources_.texture_ = texture;

    request.transform_.position_ = glm::vec2(0.25f, 0.0f);
    request.transform_.scale_ = glm::vec2(0.50f);
    request.transform_.rotation_ = pi * rotation / 2.0f;
    gfxRenderer.AddRequest(request);

    request.transform_.position_ = glm::vec2(-0.25f, 0.0f);
    request.transform_.scale_ = glm::vec2(0.25f);
    request.transform_.rotation_ = -pi * rotation;
    gfxRenderer.AddRequest(request);

    // Fill out a single instanced request for two additional squares.
    GfxRenderer2D::InstancedRequest instanced;
    instanced.resources_.mesh_ = mesh;
    instanced.resources_.shader_ = instancedShader;
    instanced.resources_.texture_ = instancedTexture;

    instanced.transform_.count_ = numInstances;
    instanced.transform_.positions_ = instancedTranslations;
    instanced.transform_.scales_ = instancedScales;
    instanced.transform_.rotations_ = instancedRotations;

    gfxRenderer.AddRequest(instanced);

    // Do one single request to test the rendering order.
    request.transform_.position_ = glm::vec2(0.0f);
    request.transform_.scale_ = glm::vec2(0.15f);
    request.transform_.rotation_ = -pi * rotation;
    gfxRenderer.AddRequest(request);
    
    gfxRenderer.SetViewportSpace(glm::vec2(1920, 1080));
    gfxRenderer.RenderRequests();
    gfxRenderer.FlushRequests();
  }

  void GSWong::Exit()
  {
  }
}