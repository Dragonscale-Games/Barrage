/* ======================================================================== */
/*!
 * \file            Renderer.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles graphics.
 */
 /* ======================================================================== */

#include "Renderer.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>

#include <iostream>
#include <stdexcept>
#include <cassert>

namespace Barrage
{
  Renderer::Renderer() : 
    framebuffer_(),
    defaultShader_(),
    fsqShader_(),
    textureManager_(),

    maxInstances_(0),

    vao_(0),
    vertexBuffer_(0),
    faceBuffer_(0),
    translationBuffer_(0),
    scaleBuffer_(0),
    rotationBuffer_(0),
    uniformBuffer_(0)
  {
  }

  void Renderer::Initialize(GLsizei framebufferWidth, GLsizei framebufferHeight)
  {
    LoadGLFunctions();

    glActiveTexture(GL_TEXTURE0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    EnableBlending();

    framebuffer_ = std::make_unique<Framebuffer>(framebufferWidth, framebufferHeight);
    CreateDefaultShader();
    CreateFsqShader();
    textureManager_.Initialize();

    SetUpUniforms();
    SetUpVertexAttributes();
  }

  void Renderer::Shutdown()
  {
    DeleteVertexAttributes();
    DeleteUniforms();
    
    textureManager_.Shutdown();
    fsqShader_.reset();
    defaultShader_.reset();
    framebuffer_.reset();
  }

  void Renderer::Draw(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::string& texture)
  {
    defaultShader_->Bind();
    textureManager_.BindTexture(texture);
    
    glBindBuffer(GL_ARRAY_BUFFER, translationBuffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2), &position);

    glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float), &rotation);

    glBindBuffer(GL_ARRAY_BUFFER, scaleBuffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2), &scale);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  void Renderer::DrawInstanced(const glm::vec2* positionArray, float* rotationArray, const glm::vec2* scaleArray, unsigned instances, const std::string& texture)
  {
    defaultShader_->Bind();
    textureManager_.BindTexture(texture);

    glBindBuffer(GL_ARRAY_BUFFER, translationBuffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, instances * sizeof(glm::vec2), positionArray);
    
    glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, instances * sizeof(float), rotationArray);
    
    glBindBuffer(GL_ARRAY_BUFFER, scaleBuffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, instances * sizeof(glm::vec2), scaleArray);
    
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instances);
  }

  void Renderer::DrawFsq()
  {
    fsqShader_->Bind();
    framebuffer_->BindTexture();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  void Renderer::ClearBackground()
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Renderer::IncreaseMaxInstances(unsigned maxInstances)
  {
    if (maxInstances <= maxInstances_)
    {
      return;
    }
    
    maxInstances_ = maxInstances;

    glBindBuffer(GL_ARRAY_BUFFER, translationBuffer_);
    glBufferData(GL_ARRAY_BUFFER, maxInstances * sizeof(glm::vec2), nullptr , GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, scaleBuffer_);
    glBufferData(GL_ARRAY_BUFFER, maxInstances * sizeof(glm::vec2), nullptr, GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer_);
    glBufferData(GL_ARRAY_BUFFER, maxInstances * sizeof(float), nullptr, GL_STREAM_DRAW);
  }

  void Renderer::SetViewport(int width, int height, int x, int y)
  {
    glViewport(x, y, width, height);
  }

  Framebuffer& Renderer::GetFramebuffer()
  {
    return *framebuffer_;
  }

  TextureManager& Renderer::Textures()
  {
    return textureManager_;
  }

  void Renderer::LoadGLFunctions()
  {
    int version = gladLoadGL(glfwGetProcAddress);

    if (!version)
    {
      throw std::runtime_error("OpenGL functions could not be loaded.");
    }
  }

  void Renderer::EnableBlending()
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void Renderer::CreateDefaultShader()
  {
    const std::string vertexSource = R"(
      #version 330 core
      
      layout (location = 0) in vec2 a_position;
      layout (location = 1) in vec2 a_tex_coord;
      
      layout (location = 2) in vec2 a_translation;
      layout (location = 3) in vec2 a_scale;
      layout (location = 4) in float a_rotation;
      
      layout(std140) uniform Matrices 
      {
        mat4 proj_matrix;
        mat4 view_matrix;
      };
      
      out vec2 tex_coord;
      
      void main()
      {
        float cos_result = cos(a_rotation);
        float sin_result = sin(a_rotation);
        
        mat4 transform_matrix = mat4( a_scale[0] * cos_result * 0.5, a_scale[0] * sin_result * 0.5, 0.0, 0.0,
                                     a_scale[1] * -sin_result * 0.5, a_scale[1] * cos_result * 0.5, 0.0, 0.0,
                                                          0.0,                     0.0, 1.0, 0.0,
                                             a_translation[0],        a_translation[1], 0.0, 1.0);
      
        gl_Position = proj_matrix * view_matrix * transform_matrix * vec4(a_position, 0.0, 1.0);
        
        tex_coord = a_tex_coord;
      }
    )";

    const std::string fragmentSource = R"(
      #version 330 core
      
      out vec4 color;
      
      in vec2 tex_coord;
      
      uniform sampler2D tex_sampler;
      
      void main()
      {
        color = texture(tex_sampler, tex_coord);
      }
    )";

    defaultShader_ = std::make_unique<Shader>(vertexSource, fragmentSource);
  }

  void Renderer::CreateFsqShader()
  {
    const std::string vertexSource = R"(
      #version 330 core
      
      layout (location = 0) in vec2 a_position;
      layout (location = 1) in vec2 a_tex_coord;
      
      out vec2 tex_coord;
      
      void main()
      {
        gl_Position =  vec4(a_position, 0.0f, 1.0);
        
        tex_coord = a_tex_coord;
      }
    )";

    const std::string fragmentSource = R"(
      #version 330 core
      
      in vec2 tex_coord;

      out vec4 frag_color;

      uniform sampler2D tex_sampler;
      
      void main()
      {
        frag_color = texture(tex_sampler, tex_coord);
      }
    )";

    fsqShader_ = std::make_unique<Shader>(vertexSource, fragmentSource);
  }


  void Renderer::SetUpUniforms()
  {
    GLuint shaderProgram = defaultShader_->GetID();
    GLuint uniformBlockIndex = glGetUniformBlockIndex(shaderProgram, "Matrices");

    GLuint bindingPoint = 0;

    glUniformBlockBinding(shaderProgram, uniformBlockIndex, bindingPoint);

    struct Matrices {
      glm::mat4 projection;
      glm::mat4 view;
    };

    Matrices matrices;
    matrices.projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, 0.1f, 100.0f);
    matrices.view = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f, -3.0f));

    glGenBuffers(1, &uniformBuffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Matrices), &matrices, GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, uniformBuffer_);
  }

  void Renderer::DeleteUniforms()
  {
    glDeleteBuffers(1, &uniformBuffer_);
  }

  void Renderer::SetUpVertexAttributes()
  {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    
    CreateQuadMesh();
    SetUpTransforms();
  }

  void Renderer::CreateQuadMesh()
  {
    float vertices[] =
    {
      -1.0f, -1.0f,      0.0f, 0.0f,
       1.0f, -1.0f,      1.0f, 0.0f,
       1.0f,  1.0f,      1.0f, 1.0f,
      -1.0f,  1.0f,      0.0f, 1.0f
    };

    unsigned faces[] =
    {
      0, 1, 2,
      0, 2, 3
    };

    // vertices
    glGenBuffers(1, &vertexBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // faces
    glGenBuffers(1, &faceBuffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
  }

  void Renderer::SetUpTransforms()
  {
    // translations
    glGenBuffers(1, &translationBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, translationBuffer_);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glVertexAttribDivisor(2, 1);

    // scales
    glGenBuffers(1, &scaleBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, scaleBuffer_);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glVertexAttribDivisor(3, 1);

    // rotations
    glGenBuffers(1, &rotationBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer_);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glVertexAttribDivisor(4, 1);

    IncreaseMaxInstances(1);
  }

  void Renderer::DeleteVertexAttributes()
  {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vertexBuffer_);
    glDeleteBuffers(1, &faceBuffer_);
    glDeleteBuffers(1, &translationBuffer_);
    glDeleteBuffers(1, &scaleBuffer_);
    glDeleteBuffers(1, &rotationBuffer_);
  }
}