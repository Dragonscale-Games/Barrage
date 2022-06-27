/* ======================================================================== */
/*!
 * \file            TestRenderer.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary renderer to make it convenient to test game systems. Will be
   replaced with David Wong's renderer, cuz it's gonna be dope.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TestRenderer_BARRAGE_H
#define TestRenderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <string>

struct GLFWwindow;

namespace Barrage
{
  class TestShader;
  class TestTexture;

  const std::string default_texture = std::string();
  const std::string default_shader = std::string();

  //! Temporary renderer for testing game systems
  class TestRenderer
  {
  public:
    static TestRenderer& Instance();

    TestRenderer(TestRenderer& other) = delete;

    void operator=(const TestRenderer& rhs) = delete;

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

    const TestTexture* boundTexture_;
    const TestShader* boundShader_;
    
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

    TestRenderer();

    void CreateWindow();

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
#endif // TestRenderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////