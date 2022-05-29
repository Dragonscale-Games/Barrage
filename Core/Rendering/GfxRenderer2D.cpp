/* ========================================================================= */
/*!
 *
 * \file            GfxManager2D.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

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

#include <stdafx.h>
#include "GfxRenderer2D.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <Rendering/GLError.hpp>

namespace Barrage
{
  GfxRenderer2D::GfxRenderer2D() :
    clearColor_(glm::vec3(0.0f), 1.0f), viewport_{ glm::mat4(1.0f) },
    manager_(nullptr), instancedBuffers_{ 0 }
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
    CHECK_GL( glClearBufferfv(GL_COLOR, 0, glm::value_ptr(clearColor_)));
    CHECK_GL( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
    // Create the Vertex Array Object for the renderer.
    CHECK_GL( glGenVertexArrays(1, &renderState_) );

    // Create the mesh responsible for drawing
    // instanced version of meshes.
    CreateInstancedMesh();
  }

  void GfxRenderer2D::Shutdown()
  {
    FlushRequests();
    // Delete the buffers that used to belong on the instanced mesh.
    CHECK_GL( glDeleteBuffers(GfxRenderer2D::BUFFER_COUNT, instancedBuffers_) );
    // Delete the Vertex Array Object.
    CHECK_GL( glDeleteVertexArrays(1, &renderState_));
  }

  void GfxRenderer2D::SetExpectedRequests(size_t requests)
  {
    requests_.reserve(requests);
  }

  void GfxRenderer2D::SetBackgroundColor(const glm::vec4& color)
  {
    clearColor_ = color;
  }

  void GfxRenderer2D::SetViewportSpace(const glm::ivec2& dimensions)
  {
    viewport_.projection_ =
      glm::ortho(
        static_cast<float>(-dimensions.x) / 2.0f,
        static_cast<float>(dimensions.x) / 2.0f,
        static_cast<float>(-dimensions.y) / 2.0f,
        static_cast<float>(dimensions.y) / 2.0f);
    CHECK_GL( glViewport(0, 0, dimensions.x, dimensions.y) );
  }

  void GfxRenderer2D::AddRequest(const InstancedRequest& request)
  {
    // This is necessary as to save the pointer dereferencing done
    // by the internal resources of the incoming request.
    // We dereference those as the resources should still exist
    // by the time we draw them.
    InternalRequest internal = {};
    // So for the mesh, we are technically going to render the 
    // instanced mesh.
    internal.resources_.meshIndex_ = request.resources_.mesh_;
    // We store the incoming mesh in another variable.
    internal.resources_.textureIndex_ = request.resources_.texture_;
    internal.resources_.shaderIndex_ = request.resources_.shader_;
    internal.resources_.framebufferIndex_ = request.resources_.framebuffer_;
    internal.transform_ = request.transform_;

    requests_.push_back(internal);
  }

  void GfxRenderer2D::RenderRequests()
  {
    // Clear the backbuffer, for now hardcoded.
    CHECK_GL( glClearBufferfv(GL_COLOR, 0, glm::value_ptr(clearColor_)) );
    //CHECK_GL( glClear(GL_COLOR_BUFFER_BIT) );

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
    
    // Bind the rendering state and the attribute formatting.
    CHECK_GL( glBindVertexArray(renderState_) );
    
    // Keep track of the previous shader bound to the pipeline.
    for (auto& renderState : requests_)
    {
      // If the previous shader is not the same ID as the current one
      // Reset the current shader and bind the new one.
      const InternalState& resource = renderState.resources_;
      if (current_.shaderIndex_ != resource.shaderIndex_)
      {
        current_.shaderIndex_ = resource.shaderIndex_;
        int shaderID = static_cast<int>(resourceShaders[current_.shaderIndex_]);
        CHECK_GL( glUseProgram(shaderID) );
        // Set the uniform for the projection matrix.
        GLint projectionUniform = glGetUniformLocation(shaderID, "projection");
        CHECK_GL((void)0);
        if (projectionUniform != -1)
        {
          CHECK_GL( glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(viewport_.projection_)) );
        }
      }
      // If the previous mesh is not the same ID as the current one.
      // Reset the previous mesh and bind the new one.
      if (current_.meshIndex_ != resource.meshIndex_)
      {
        // Save the currently bound mesh.
        current_.meshIndex_ = resource.meshIndex_;
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
      RenderInstancedMesh(resourceShaders[current_.shaderIndex_], meshData, renderState, manager_);
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
    const std::vector<GfxManager2D::BufferList>& buffers = manager_->GetOpenGLBuffers();
    const GfxManager2D::BufferList instancedMeshBuffers = buffers[instancedMesh_];

    // Start operating on the mesh.
    CHECK_GL( glBindVertexArray(renderState_));
    BindMeshBuffers(instancedMeshBuffers);
    
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

    // -> Point the buffers for the input mesh data for this instanced mesh.
    BindMeshBuffers(requestBuffers);

    // -> Set the instanced buffer with the transform data necessary.
    
    // Set the data for the translation, scale, and rotation buffers.
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[TRANSLATION_BUFFER]) );
    CHECK_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * request.transform_.count_,
      request.transform_.positions_, GL_STREAM_DRAW) );
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[SCALE_BUFFER]) );
    CHECK_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * request.transform_.count_,
      request.transform_.scales_, GL_STREAM_DRAW) );
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedBuffers_[ROTATION_BUFFER]) );
    CHECK_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(float) * request.transform_.count_,
      request.transform_.rotations_, GL_STREAM_DRAW) );

    // Make sure to bind the correct buffer.
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, instancedVertexBuffers[GfxManager2D::VERTICES]) );
    // Now the mesh is ready to be drawn.
    const int numMeshesDrawn = request.transform_.count_;
    CHECK_GL( glDrawElementsInstanced(GL_TRIANGLES, 3U * requestMesh.faceCount_, GL_UNSIGNED_INT, nullptr, numMeshesDrawn) );
  }

  void GfxRenderer2D::BindMeshBuffers(const GfxManager2D::BufferList& buffers)
  {
    // And make sure to include the element index buffer.
    CHECK_GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[GfxManager2D::FACES]) );
    // Start binding buffers under new attribute locations.
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, buffers[GfxManager2D::VERTICES]) );
    constexpr GLint positionIndex = 0;
    constexpr GLint uvIndex = 1;
    // Setup the input layout for the vertex buffer.
    // Set up the layout for positions.
    CHECK_GL( glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0)) );
    // Set up the layout for uvs.
    CHECK_GL( glVertexAttribPointer(
      uvIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position_))) );
    // Enable the basic attributes for this rendering state.
    CHECK_GL( glEnableVertexAttribArray(positionIndex) );
    CHECK_GL( glEnableVertexAttribArray(uvIndex) );
  }
}
