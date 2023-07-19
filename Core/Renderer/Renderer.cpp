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

#include <iostream>
#include <stdexcept>

namespace Barrage
{
  Renderer* Renderer::Instance = nullptr;
  
  void Renderer::WindowResizeCallback(GLFWwindow* window, int width, int height)
  {
    window;
    glViewport(0, 0, width, height);

    if (Instance)
    {
      Instance->ResizeFramebuffer(width, height);
    }
  }

  Renderer::Renderer() :
    window_(nullptr),

    shaderManager_(),
    textureManager_(),

    boundShader_(nullptr),
    boundTexture_(nullptr),

    viewMat_(),
    projMat_(),

    vao_(0),
    vertexBuffer_(0),
    faceBuffer_(0),
    translationBuffer_(0),
    scaleBuffer_(0),
    rotationBuffer_(0),

    transformUniform_(-1),
    viewUniform_(-1),
    projectionUniform_(-1),
    textureUniform_(-1),

    fbo_(0),
    fboTex_(0)
  {
  }

  void Renderer::Initialize()
  {
    glfwInit();

    CreateGLFWWindow();

    LoadGLFunctions();

    Instance = this;

    CreateFramebuffer();

    glfwMaximizeWindow(window_);

    viewMat_ = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f, -3.0f));
    projMat_ = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, 0.1f, 100.0f);

    BindShader("Default");

    CreateQuadMesh();

    EnableBlending();

    glActiveTexture(GL_TEXTURE0);
  }

  void Renderer::Shutdown()
  {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vertexBuffer_);
    glDeleteBuffers(1, &faceBuffer_);
    glDeleteBuffers(1, &translationBuffer_);
    glDeleteBuffers(1, &scaleBuffer_);
    glDeleteBuffers(1, &rotationBuffer_);

    textureManager_.UnloadTextures();
    shaderManager_.UnloadShaders();

    Instance = nullptr;

    glfwDestroyWindow(window_);

    glfwTerminate();
  }

  void Renderer::StartFrame()
  {
    SetBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  }

  void Renderer::EndFrame()
  {
    glfwSwapBuffers(window_);
  }

  void Renderer::StartFramebufferRendering()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    SetBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  }

  void Renderer::EndFramebufferRendering()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  bool Renderer::WindowClosed()
  {
    return glfwWindowShouldClose(window_);
  }

  void Renderer::Draw(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::string& texture)
  {
    glm::mat4 scale_mat = glm::scale(glm::identity<glm::mat4>(), glm::vec3(scale, 1.0f));

    glm::mat4 rotation_mat = glm::rotate(glm::identity <glm::mat4>(), rotation, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 translation_mat = glm::translate(glm::identity<glm::mat4>(), glm::vec3(position, 0.0f));

    glm::mat4 transform = translation_mat * rotation_mat * scale_mat;

    Draw(transform, texture);
  }

  void Renderer::Draw(const glm::mat4& transform, const std::string& texture)
  {
    BindShader("Default");
    BindTexture(texture);

    glUniformMatrix4fv(transformUniform_, 1, false, &transform[0][0]);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  void Renderer::DrawInstanced(const glm::vec2* positionArray, float* rotationArray, const glm::vec2* scaleArray, unsigned instances, const std::string& texture)
  {
    BindShader("Instanced");
    BindTexture(texture);

    glBindBuffer(GL_ARRAY_BUFFER, translationBuffer_);
    glBufferData(GL_ARRAY_BUFFER, instances * sizeof(glm::vec2), &positionArray[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, scaleBuffer_);
    glBufferData(GL_ARRAY_BUFFER, instances * sizeof(glm::vec2), &scaleArray[0], GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer_);
    glBufferData(GL_ARRAY_BUFFER, instances * sizeof(float), &rotationArray[0], GL_STREAM_DRAW);

    glBindVertexArray(vao_);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instances);
  }

  void Renderer::DrawFSQ()
  {
    glm::mat4 scale_mat = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1920.0f, 1080.0f, 1.0f));

    glm::mat4 rotation_mat = glm::rotate(glm::identity <glm::mat4>(), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 translation_mat = glm::translate(glm::identity<glm::mat4>(), glm::vec3(960.0f, 540.0f, 0.0f));

    glm::mat4 transform = translation_mat * rotation_mat * scale_mat;

    BindShader("Default");
    glBindTexture(GL_TEXTURE_2D, fboTex_);

    glUniformMatrix4fv(transformUniform_, 1, false, &transform[0][0]);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    if (boundTexture_)
    {
      glBindTexture(GL_TEXTURE_2D, boundTexture_->GetID());
    }
  }

  GLuint Renderer::GetFramebufferID()
  {
    return fbo_;
  }

  void Renderer::ResizeFramebuffer(int width, int height)
  {
    glBindTexture(GL_TEXTURE_2D, fboTex_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void Renderer::CreateGLFWWindow()
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(START_WIDTH, START_HEIGHT, "Barrage", NULL, NULL);
    if (window_ == NULL)
    {
      throw std::runtime_error("Window could not be created.");
    }

    glfwMakeContextCurrent(window_);
  }

  GLFWwindow* Renderer::GetWindowHandle()
  {
    return window_;
  }

  void Renderer::SetBackgroundColor(const glm::vec4& color)
  {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Renderer::LoadGLFunctions()
  {
    int version = gladLoadGL(glfwGetProcAddress);

    if (!version)
    {
      throw std::runtime_error("OpenGL functions could not be loaded.");
    }
  }

  void Renderer::CreateFramebuffer()
  {
    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);

    glGenTextures(1, &fboTex_);
    glBindTexture(GL_TEXTURE_2D, fboTex_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, START_WIDTH, START_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTex_, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      std::cout << "Framebuffer not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glfwSetFramebufferSizeCallback(window_, WindowResizeCallback);
  }

  void Renderer::GetUniformLocations()
  {
    transformUniform_ = glGetUniformLocation(boundShader_->GetID(), "transform_matrix");
    viewUniform_ = glGetUniformLocation(boundShader_->GetID(), "view_matrix");
    projectionUniform_ = glGetUniformLocation(boundShader_->GetID(), "proj_matrix");
    textureUniform_ = glGetUniformLocation(boundShader_->GetID(), "tex_sampler");
  }

  void Renderer::SetUniforms()
  {
    GetUniformLocations();

    glUniformMatrix4fv(viewUniform_, 1, false, &viewMat_[0][0]);
    glUniformMatrix4fv(projectionUniform_, 1, false, &projMat_[0][0]);
  }

  void Renderer::CreateQuadMesh()
  {
    float vertices[] =
    {
      -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
       0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
       0.5f,  0.5f, 0.0f,      1.0f, 1.0f,
      -0.5f,  0.5f, 0.0f,      0.0f, 1.0f
    };

    unsigned faces[] =
    {
      0, 1, 2,
      0, 2, 3
    };

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertexBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glGenBuffers(1, &faceBuffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glGenBuffers(1, &translationBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, translationBuffer_);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    glVertexAttribDivisor(2, 1);

    glGenBuffers(1, &scaleBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, scaleBuffer_);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    glVertexAttribDivisor(3, 1);

    glGenBuffers(1, &rotationBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, rotationBuffer_);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

    glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);
  }

  void Renderer::EnableBlending()
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void Renderer::BindTexture(const std::string& textureName)
  {
    const Texture* texture = textureManager_.GetTexture(textureName);

    glBindTexture(GL_TEXTURE_2D, texture->GetID());

    boundTexture_ = texture;
  }

  void Renderer::BindShader(const std::string& shaderName)
  {
    const Shader* shader = shaderManager_.GetShader(shaderName);
    glUseProgram(shader->GetID());

    boundShader_ = shader;

    SetUniforms();
  }
}