/* ======================================================================== */
/*!
 * \file            Renderer.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles drawing/graphics.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Renderer_BARRAGE_H
#define Renderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

#include "Framebuffers/Framebuffer.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/TextureManager.hpp"

namespace Barrage
{
  //! Handles drawing/graphics
  class Renderer
  {
    public:  
      Renderer();

      void Initialize(GLsizei framebufferWidth, GLsizei framebufferHeight);

      void Shutdown();

      void Draw(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::string& texture);

      void DrawInstanced(const glm::vec2* positionArray, float* rotationArray, const glm::vec2* scaleArray, unsigned instances, const std::string& texture);

      void DrawFsq();

      void ClearBackground();

      void IncreaseMaxInstances(unsigned maxInstances);

      void SetViewport(int width, int height, int x = 0, int y = 0);

      Framebuffer& GetFramebuffer();

      TextureManager& Textures();

    private:
      std::unique_ptr<Framebuffer> framebuffer_;
      std::unique_ptr<Shader> defaultShader_;
      std::unique_ptr<Shader> fsqShader_;
      TextureManager textureManager_;

      unsigned maxInstances_;

      GLuint vao_;
      GLuint vertexBuffer_;
      GLuint faceBuffer_;
      GLuint translationBuffer_;
      GLuint scaleBuffer_;
      GLuint rotationBuffer_;
      GLuint uniformBuffer_;

      void LoadGLFunctions();

      void EnableBlending();

      void CreateDefaultShader();

      void CreateFsqShader();

      void SetUpUniforms();

      void DeleteUniforms();

      void SetUpVertexAttributes();

      void CreateQuadMesh();

      void SetUpTransforms();

      void DeleteVertexAttributes();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Renderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////