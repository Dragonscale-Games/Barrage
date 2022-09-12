/*
MIT License

Copyright(c) 2022 Dragonscale-Games

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ======================================================================== */
/*!
 * \file            SimpleRenderer.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Simple renderer, good for debugging or demo projects.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SimpleRenderer_BARRAGE_H
#define SimpleRenderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <string>

#include "SimpleShader/SimpleShaderManager.hpp"
#include "SimpleTexture/SimpleTextureManager.hpp"

struct GLFWwindow;

namespace Barrage
{
  const std::string default_texture = std::string();
  const std::string default_shader = std::string();

  //! Simple renderer for debugging/demos
  class SimpleRenderer
  {
  public:
    SimpleRenderer();

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

    SimpleShaderManager shaderManager_;
    SimpleTextureManager textureManager_;

    const SimpleTexture* boundTexture_;
    const SimpleShader* boundShader_;
    
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
#endif // SimpleRenderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////