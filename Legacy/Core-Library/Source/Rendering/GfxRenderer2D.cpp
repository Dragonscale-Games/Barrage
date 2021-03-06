/* ========================================================================= */
/*!
 *
 * \file            GfxManager2D.cpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Defines the interface used to initialize all graphics.
 * Responsible with creating the context for the window and managing
 * all the resources used to render anything to the screen (e.g. shaders,
 * meshes, framebuffer).
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include "GfxRenderer2D.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>              // std::copy
#include <limits>                 // std::numeric_limits

#include "../GLError.hpp"

namespace Barrage
{
  GfxRenderer2D::GfxRenderer2D() :
    manager_(nullptr), clearColor_(glm::vec3(0.0f), 1.0f), viewport_{ glm::mat4(1.0f) }, instancedBuffers_{ 0 }
  {
  }

  void GfxRenderer2D::Initialize(GfxManager2D& manager)
  {
    // Get the manager to create the resources from.
    manager_ = &manager;
    // Setup the rendering settings for this renderer.
    CHECK_GL( glDisable(GL_CULL_FACE) );
    CHECK_GL( glDisable(GL_DEPTH_TEST) );
    CHECK_GL( glEnable(GL_BLEND) );

    CHECK_GL( glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a) );
    CHECK_GL( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    // Create the mesh responsible for drawing
    // instanced version of meshes.
    CreateInstancedMesh();
  }

  void GfxRenderer2D::Shutdown()
  {
    FlushRequests();
    // Delete the buffers that used to belong on the instanced mesh.
    CHECK_GL( glDeleteBuffers(GfxRenderer2D::BUFFER_COUNT, instancedBuffers_) );
  }

  void GfxRenderer2D::SetExpectedRequests(size_t requests)
  {
    requests_.reserve(requests);
  }

  void GfxRenderer2D::SetBackgroundColor(const glm::vec4& color)
  {
    clearColor_ = color;
  }

  void GfxRenderer2D::SetViewportSpace(const glm::vec2& dimensions)
  {
    viewport_.projection_ = glm::ortho(-dimensions.x / 2.0f, dimensions.x / 2.0f, -dimensions.y / 2.0f, dimensions.y / 2.0f);
  }

  void GfxRenderer2D::AddRequest(const SingleRequest& request)
  {
    // This is necessary as to save the pointer dereferencing done
    // by the internal resources of the incoming request.
    // We dereference those as the resources should still exist
    // by the time we draw them.
    InternalRequest internal;
    internal.type_ = REQUEST_SINGLE;
    internal.resources_.meshIndex_ = request.resources_.mesh_;
    internal.resources_.textureIndex_ = request.resources_.texture_;
    internal.resources_.shaderIndex_ = request.resources_.shader_;
    internal.resources_.framebufferIndex_ = request.resources_.framebuffer_;
    internal.transform_.single_ = request.transform_;
    // Zero out the instanced data to avoid baaaad stuff.
    std::memset(&internal.transform_.instanced_, 0, sizeof(InstancedTransformData));

    requests_.push_back(internal);
  }

  void GfxRenderer2D::AddRequest(const InstancedRequest& request)
  {
    // This is necessary as to save the pointer dereferencing done
    // by the internal resources of the incoming request.
    // We dereference those as the resources should still exist
    // by the time we draw them.
    InternalRequest internal;
    internal.type_ = REQUEST_INSTANCED;
    // So for the mesh, we are technically going to render the 
    // instanced mesh.
    internal.resources_.meshIndex_ = request.resources_.mesh_;
    // We store the incoming mesh in another variable.
    internal.resources_.textureIndex_ = request.resources_.texture_;
    internal.resources_.shaderIndex_ = request.resources_.shader_;
    internal.resources_.framebufferIndex_ = request.resources_.framebuffer_;
    internal.transform_.instanced_ = request.transform_;
    // Zero out the single data to avoid baaaad stuff.
    std::memset(&internal.transform_.single_, 0, sizeof(SingleTransformData));

    requests_.push_back(internal);
  }

  void GfxRenderer2D::RenderRequests()
  {
    // Clear the backbuffer, for now hardcoded.
    CHECK_GL( glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a) );
    CHECK_GL( glClear(GL_COLOR_BUFFER_BIT) );

    // Render all the requests.
    // Get the list of shaders.
    const std::vector<GLuint>& resourceShaders = manager_->GetOpenGLShaders();
    // Get the list of meshes.
    const std::vector<GfxManager2D::MeshData>& resourceMeshes = manager_->GetOpenGLMeshes();
    // Get the list of textures.
    const std::vector<GfxManager2D::TextureData>& resourceTextures = manager_->GetOpenGLTextures();

    // Quit out early if empty.
    if (requests_.empty())
    {
      return;
    }

    // Clear the set of resources being used so they are bound.
    current_.meshIndex_ = -1;
    current_.shaderIndex_ = -1;
    current_.textureIndex_ = -1;
    current_.framebufferIndex_ = -1;
    // Keep track of whether we have rendered a single or instanced request.
    RequestType type = REQUEST_SINGLE;

    // Keep track of the previous shader bound to the pipeline.
    for (auto& renderState : requests_)
    {
      // If the previous shader is not the same ID as the current one
      // Reset the current shader and bind the new one.
      const InternalState& resource = renderState.resources_;
      if (current_.shaderIndex_ != resource.shaderIndex_)
      {
        current_.shaderIndex_ = resource.shaderIndex_;
        int shaderID = resourceShaders[current_.shaderIndex_];
        CHECK_GL( glUseProgram(shaderID) );
        // Set the uniform for the projection matrix.
        GLint projectionUniform = glGetUniformLocation(shaderID, "projection");
        CHECK_GL();
        if (projectionUniform != -1)
        {
          CHECK_GL( glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(viewport_.projection_)) );
        }
      }
      // If the previous mesh is not the same ID as the current one.
      // Reset the previous mesh and bind the new one.

      if (current_.meshIndex_ != resource.meshIndex_ || type != renderState.type_)
      {
        // Save the currently bound mesh.
        current_.meshIndex_ = resource.meshIndex_;
        // And the type of request drawn.
        type = renderState.type_;
        // And bind the mesh to the OpenGL pipeline.
        switch (renderState.type_)
        {
        case REQUEST_SINGLE:
          CHECK_GL( glBindVertexArray(resourceMeshes[current_.meshIndex_].internalMeshID_) );
          break;
        case REQUEST_INSTANCED:
          CHECK_GL( glBindVertexArray(resourceMeshes[instancedMesh_].internalMeshID_) );
          break;
        }
      }
      // If the previous texture is not the same ID as the current one.
      // Reset the previous texture and bind the new one.
      if (current_.textureIndex_ != resource.textureIndex_)
      {
        current_.textureIndex_ = resource.textureIndex_;
        const GfxManager2D::TextureData& data = resourceTextures[current_.textureIndex_];
        CHECK_GL( glBindTexture(data.textureType_, data.internalTextureID_) );
        CHECK_GL( glActiveTexture(GL_TEXTURE0) );
      }

      const GfxManager2D::MeshData& meshData = resourceMeshes[current_.meshIndex_];
      // Finally, render the correct algorithm.
      switch (renderState.type_)
      {
      case REQUEST_SINGLE:
        RenderSingleMesh(resourceShaders[current_.shaderIndex_], meshData, renderState, manager_);
        break;
      case REQUEST_INSTANCED:
        RenderInstancedMesh(resourceShaders[current_.shaderIndex_], meshData, renderState, manager_);
        break;
      }
    }

    CHECK_GL( glBindVertexArray(0) );
  }

  void GfxRenderer2D::FlushRequests()
  {
    requests_.clear();
  }

  const glm::vec4& GfxRenderer2D::GetBackgroundColor() const
  {
    return clearColor_;
  }
  
  void GfxRenderer2D::CreateInstancedMesh()
  {
    // Create the mesh for the instance requests.
    instancedMesh_ = manager_->CreateMesh();
    // Create the buffers needed for the instanced mesh.
    // This is too specific to really be done well in the gfx manager soo.....
    // Create and manage these buffers.
    CHECK_GL( glGenBuffers(BUFFER_COUNT, instancedBuffers_) );
    // Bind these buffers under the mesh with the attribute divisor on.
    // The meshes to to perform the OpenGL code with.
    const std::vector<GfxManager2D::MeshData>& resourceMeshes = manager_->GetOpenGLMeshes();
    const std::vector<GfxManager2D::BufferList>& buffers = manager_->GetOpenGLBuffers();
    const GfxManager2D::BufferList instancedMeshBuffers = buffers[instancedMesh_];

    // Start operating on the meshs.
    CHECK_GL( glBindVertexArray(resourceMeshes[instancedMesh_].internalMeshID_) );
    // And make sure to include the element index buffer.
    CHECK_GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, instancedMeshBuffers[GfxManager2D::FACES]) );
    // Start binding buffers under new attribute locations.
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedMeshBuffers[GfxManager2D::VERTICES]) );
    const GLint positionIndex = 0;
    const GLint uvIndex = 1;
    // Setup the input layout for the vertex buffer.
    // Set up the layout for positions.
    CHECK_GL( glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, sizeof(GfxManager2D::Vertex), reinterpret_cast<void*>(0)) );
    CHECK_GL( glEnableVertexAttribArray(positionIndex) );
    // Set up the layout for uvs.
    CHECK_GL( glVertexAttribPointer(
      uvIndex, 2, GL_FLOAT, GL_FALSE, sizeof(GfxManager2D::Vertex), reinterpret_cast<void*>(sizeof(glm::vec2))) );
    CHECK_GL( glEnableVertexAttribArray(uvIndex) );
    // Setup the layout for the instanced transform data buffers.
    const GLint translationIndex = 2;
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[TRANSLATION_BUFFER]) );
    CHECK_GL( glVertexAttribPointer(translationIndex, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(0)) );
    CHECK_GL( glVertexAttribDivisor(translationIndex, 1) );

    const GLint scaleIndex = 3;
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[SCALE_BUFFER]) );
    CHECK_GL( glVertexAttribPointer(scaleIndex, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(0)) );
    CHECK_GL( glVertexAttribDivisor(scaleIndex, 1) );

    const GLint rotationIndex = 4;
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[ROTATION_BUFFER]) );
    CHECK_GL( glVertexAttribPointer(rotationIndex, 1, GL_FLOAT, GL_FALSE, sizeof(float), reinterpret_cast<void*>(0)) );
    CHECK_GL( glVertexAttribDivisor(rotationIndex, 1) );

    // Enable the vertex attributes being used.
    CHECK_GL( glEnableVertexAttribArray(translationIndex) );
    CHECK_GL( glEnableVertexAttribArray(scaleIndex) );
    CHECK_GL( glEnableVertexAttribArray(rotationIndex) );

    // Unbind the instanced mesh.
    CHECK_GL( glBindVertexArray(0) );
  }

  void GfxRenderer2D::RenderSingleMesh(
    const GLuint shaderID,
    const GfxManager2D::MeshData& data,
    const InternalRequest& request,
    const GfxManager2D* manager)
  {
    UNREFERENCED(manager);
    
    // Get the uniform locations.
    GLint translationUniform = glGetUniformLocation(shaderID, "translation");
    GLint scaleUniform = glGetUniformLocation(shaderID, "scale");
    GLint rotationUniform = glGetUniformLocation(shaderID, "rotation");
    GLint textureUniform = glGetUniformLocation(shaderID, "diffuse");
    CHECK_GL();
    // Set the values for the uniforms.
    if (translationUniform != -1)
    {
      glUniform2fv(translationUniform, 1, glm::value_ptr(request.transform_.single_.position_));
    }
    if (scaleUniform != -1)
    {
      glUniform2fv(scaleUniform, 1, glm::value_ptr(request.transform_.single_.scale_));
    }
    if (rotationUniform != -1)
    {
      glUniform1f(rotationUniform, request.transform_.single_.rotation_);
    }
    if (textureUniform != -1)
    {
      glUniform1i(textureUniform, 0);
    }
    CHECK_GL();

    // Enable the vertex attributes separately for every specific mesh.
    const int positionIndex = 0;
    const int uvIndex = 1;
    CHECK_GL( glEnableVertexAttribArray(positionIndex) );
    CHECK_GL( glEnableVertexAttribArray(uvIndex) );
    // Now the mesh is ready for rendering.
    CHECK_GL( glDrawElements(GL_TRIANGLES, 3 * data.faceCount_, GL_UNSIGNED_INT, nullptr) );
    // Disable the vertices after.
    CHECK_GL( glDisableVertexAttribArray(positionIndex) );
    CHECK_GL( glDisableVertexAttribArray(uvIndex) );
  }

  void GfxRenderer2D::RenderInstancedMesh(
    const GLuint shaderID, 
    const GfxManager2D::MeshData& data, 
    const InternalRequest& request,
    const GfxManager2D* manager)
  {
    UNREFERENCED(shaderID);
    UNREFERENCED(data);
    UNREFERENCED(request);
    UNREFERENCED(manager);

    // Remember that the mesh index for instanced requests will always be the instanced mesh.
    // You can get the index to the source mesh using the sourceMeshIndex member variable.

    // Get the list of available meshes.
    const std::vector<GfxManager2D::MeshData>& resourceMeshes = manager->GetOpenGLMeshes();
    // Get the list of available buffers.
    const std::vector<GfxManager2D::BufferList>& resourceBuffers = manager->GetOpenGLBuffers();

    // Get the meshes found in the request.
    const GfxManager2D::MeshData& requestMesh = resourceMeshes[request.resources_.meshIndex_];
    // Get the buffers found in the request.
    const GfxManager2D::BufferList requestBuffers = resourceBuffers[request.resources_.meshIndex_];
    // Get the buffers found in the instance buffer.
    const GfxManager2D::BufferList instancedVertexBuffers = resourceBuffers[instancedMesh_];

    // -> Copy the buffers from the mesh buffer data in the request over to the instanced mesh.
    
    // Copy over the vertices first.
    const size_t vertexBufferSize = requestMesh.vertexCount_ * sizeof(GfxManager2D::Vertex);
    CHECK_GL( glBindBuffer(GL_COPY_READ_BUFFER, requestBuffers[GfxManager2D::VERTICES]) );
    CHECK_GL( glBindBuffer(GL_COPY_WRITE_BUFFER, instancedVertexBuffers[GfxManager2D::VERTICES]) );
    CHECK_GL( glBufferData(GL_COPY_WRITE_BUFFER, vertexBufferSize, nullptr, GL_STREAM_DRAW) );

    CHECK_GL( glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, vertexBufferSize) );

    // Then copy over the faces.
    const size_t faceBufferSize = requestMesh.faceCount_ * sizeof(GfxManager2D::Face);
    CHECK_GL( glBindBuffer(GL_COPY_READ_BUFFER, requestBuffers[GfxManager2D::FACES]) );
    CHECK_GL( glBindBuffer(GL_COPY_WRITE_BUFFER, instancedVertexBuffers[GfxManager2D::FACES]) );
    CHECK_GL( glBufferData(GL_COPY_WRITE_BUFFER, faceBufferSize, nullptr, GL_STREAM_DRAW) );

    CHECK_GL( glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, faceBufferSize) );

    // Unbind the copy read and write buffers.
    CHECK_GL( glBindBuffer(GL_COPY_READ_BUFFER, 0) );
    CHECK_GL( glBindBuffer(GL_COPY_WRITE_BUFFER, 0) );

    // -> Set the instanced buffer with the transform data necessary.
    
    // Set the data for the translation, scale, and rotation buffers.
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[TRANSLATION_BUFFER]) );
    CHECK_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * request.transform_.instanced_.count_,
      request.transform_.instanced_.positions_, GL_STREAM_DRAW) );
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[SCALE_BUFFER]) );
    CHECK_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * request.transform_.instanced_.count_,
      request.transform_.instanced_.scales_, GL_STREAM_DRAW) );
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[ROTATION_BUFFER]) );
    CHECK_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(float) * request.transform_.instanced_.count_,
      request.transform_.instanced_.rotations_, GL_STREAM_DRAW) );

    // Make sure to bind the correct buffer.
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedVertexBuffers[GfxManager2D::VERTICES]) );
    // Now the mesh is ready to be drawn.
    const int numMeshesDrawn = request.transform_.instanced_.count_;
    CHECK_GL( glDrawElementsInstanced(GL_TRIANGLES, 3U * requestMesh.faceCount_, GL_UNSIGNED_INT, nullptr, numMeshesDrawn) );
  }
}
