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

#include "Framebuffers/Framebuffer.hpp"
#include "Shaders/Shader.hpp"
#include "Textures/TextureManager.hpp"
#include "RendererTypes.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

namespace Barrage
{
  //! Handles drawing/graphics
  class Renderer
  {
    public:  
      Renderer();

      void Initialize(GLsizei framebufferWidth, GLsizei framebufferHeight);

      void Shutdown();

      void Draw(
        const Position& position, 
        const Rotation& rotation, 
        const Scale& scale, 
        const ColorTint& colorTint, 
        const TextureUV& textureUV, 
        const std::string& texture
      );

      void DrawInstanced(
        const Position* positionArray,
        const Rotation* rotationArray,
        const Scale* scaleArray,
        const ColorTint* colorTintArray,
        const TextureUV* textureUVArray,
        unsigned instances, 
        const std::string& texture
      );

      void DrawFsq();

      void ClearBackground();

      void ReserveInstances(unsigned numInstances);

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
      GLuint colorTintBuffer_;
      GLuint textureUVBuffer_;
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

      void SetUpColorTints();

      void SetUpTextureUVs();

      void DeleteVertexAttributes();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Renderer_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////