/* ======================================================================== */
/*!
 * \file            Renderer.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles graphics.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Renderer_BARRAGE_H
#define Renderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <string>

#include "Shaders/ShaderManager.hpp"
#include "Textures/TextureManager.hpp"

struct GLFWwindow;

namespace Barrage
{
  const std::string default_texture = std::string();
  const std::string default_shader = std::string();

  //! Simple renderer for debugging/demos
  class Renderer
  {
  public:
    Renderer();

    void Initialize();

    void Shutdown();

    void StartFrame();

    void EndFrame();

    bool WindowClosed();

    GLFWwindow* GetWindowHandle();

    void Draw(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::string& texture = default_texture);

    void Draw(const glm::mat4& transform, const std::string& texture = default_texture);

    void DrawInstanced(const glm::vec2* positionArray, float* rotationArray, const glm::vec2* scaleArray, unsigned instances, const std::string& texture = default_texture);

  private:
    GLFWwindow* window_;

    ShaderManager shaderManager_;
    TextureManager textureManager_;

    const Texture* boundTexture_;
    const Shader* boundShader_;

    glm::mat4 viewMat_;
    glm::mat4 projMat_;

    unsigned vao_;
    unsigned vertexBuffer_;
    unsigned faceBuffer_;
    unsigned translationBuffer_;
    unsigned scaleBuffer_;
    unsigned rotationBuffer_;

    int transformUniform_;
    int viewUniform_;
    int projectionUniform_;
    int textureUniform_;

    void CreateGLFWWindow();

    void SetBackgroundColor(const glm::vec4& color);

    void LoadGLFunctions();

    void GetUniformLocations();

    void SetUniforms();

    void CreateQuadMesh();

    void EnableBlending();

    void BindTexture(const std::string& textureName);

    void BindShader(const std::string& shader_name);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Renderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////