/* ======================================================================== */
/*!
 * \file            TestRenderer.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary renderer to make it convenient to test game systems. Will be
   replaced with David Wong's renderer, cuz it's gonna be dope.

 */
 /* ======================================================================== */

#include "stdafx.h"

#include "TestRenderer.hpp"
#include "TempShader/TestShaderManager.hpp"
#include "TempTexture/TestTextureManager.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdexcept>

namespace Barrage
{
  static void WindowResizeCallback(GLFWwindow* window, int width, int height)
  {
    (void)window;
    glViewport(0, 0, width, height);
  }

  TestRenderer& TestRenderer::Instance()
  {
    static TestRenderer instance;
    return instance;
  }

  TestRenderer::TestRenderer() :
    window_(nullptr),

    boundTexture_(nullptr),
    boundShader_(nullptr),

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
    textureUniform_(-1)
  {
  }

  void TestRenderer::Initialize()
  {
    glfwInit();

    CreateWindow();

    //glfwSwapInterval(0);

    LoadGLFunctions();

    viewMat_ = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0f, 0.0f, -3.0f));
    projMat_ = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f);

    BindShader("Default");

    CreateQuadMesh();

    EnableBlending();

    glActiveTexture(GL_TEXTURE0);
  }

  void TestRenderer::Shutdown()
  {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vertexBuffer_);
    glDeleteBuffers(1, &faceBuffer_);
    glDeleteBuffers(1, &translationBuffer_);
    glDeleteBuffers(1, &scaleBuffer_);
    glDeleteBuffers(1, &rotationBuffer_);

    TestTextureManager::Instance().UnloadTexture("All");
    TestShaderManager::Instance().UnloadShaders();

    glfwDestroyWindow(window_);

    glfwTerminate();
  }

  void TestRenderer::StartFrame()
  {
    SetBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  }

  void TestRenderer::EndFrame()
  {
    glfwSwapBuffers(window_);
  }

  bool TestRenderer::WindowClosed()
  {
    return glfwWindowShouldClose(window_);
  }

  void TestRenderer::Draw(const glm::vec2& position, float rotation, const glm::vec2& scale, const std::string& texture)
  {
    glm::mat4 scale_mat = glm::scale(glm::identity<glm::mat4>(), glm::vec3(scale, 1.0f));

    glm::mat4 rotation_mat = glm::rotate(glm::identity <glm::mat4>(), rotation, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 translation_mat = glm::translate(glm::identity<glm::mat4>(), glm::vec3(position, 0.0f) + glm::vec3(640.0f, 360.0f, 1.0f));

    glm::mat4 transform = translation_mat * rotation_mat * scale_mat;

    Draw(transform, texture);
  }

  void TestRenderer::Draw(const glm::mat4& transform, const std::string& texture)
  {
    BindShader("Default");
    BindTexture(texture);

    glUniformMatrix4fv(transformUniform_, 1, false, &transform[0][0]);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  void TestRenderer::DrawInstanced(const glm::vec2* positionArray, float* rotationArray, const glm::vec2* scaleArray, unsigned instances, const std::string& texture)
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

  void TestRenderer::CreateWindow()
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(1280, 720, "Barrage Test Window", NULL, NULL);
    if (window_ == NULL)
    {
      throw std::runtime_error("Window could not be created.");
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, WindowResizeCallback);
  }

  GLFWwindow* TestRenderer::GetWindowHandle()
  {
    return window_;
  }

  void TestRenderer::SetBackgroundColor(const glm::vec4& color)
  {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void TestRenderer::LoadGLFunctions()
  {
    int version = gladLoadGL(glfwGetProcAddress);

    if (!version)
    {
      throw std::runtime_error("OpenGL functions could not be loaded.");
    }
  }

  void TestRenderer::GetUniformLocations()
  {
    transformUniform_ = glGetUniformLocation(boundShader_->GetID(), "transform_matrix");
    viewUniform_ = glGetUniformLocation(boundShader_->GetID(), "view_matrix");
    projectionUniform_ = glGetUniformLocation(boundShader_->GetID(), "proj_matrix");
    textureUniform_ = glGetUniformLocation(boundShader_->GetID(), "tex_sampler");
  }

  void TestRenderer::SetUniforms()
  {
    GetUniformLocations();

    glUniformMatrix4fv(viewUniform_, 1, false, &viewMat_[0][0]);
    glUniformMatrix4fv(projectionUniform_, 1, false, &projMat_[0][0]);
  }

  void TestRenderer::CreateQuadMesh()
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

  void TestRenderer::EnableBlending()
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void TestRenderer::BindTexture(const std::string& textureName)
  {
    const TestTexture* texture;

    if (textureName.empty())
    {
      texture = TestTextureManager::Instance().GetTexture("Default");
    }
    else
    {
      texture = TestTextureManager::Instance().GetTexture(textureName);
    }

    if (texture != boundTexture_)
    {
      glBindTexture(GL_TEXTURE_2D, texture->GetID());

      boundTexture_ = texture;
    }
  }

  void TestRenderer::BindShader(const std::string& shaderName)
  {
    const TestShader* shader;

    if (shaderName.empty())
    {
      shader = TestShaderManager::Instance().GetShader("Default");
    }
    else
    {
      shader = TestShaderManager::Instance().GetShader(shaderName);
    }

    if (shader != boundShader_)
    {
      glUseProgram(shader->GetID());

      boundShader_ = shader;

      SetUniforms();
    }
  }
}