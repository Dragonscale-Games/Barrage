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

// ============================================================================
// Includes
// ============================================================================

//#include "stdafx.h"
#include "GLError.hpp"
#include "GfxManager2D.hpp"
#include "WindowManager.hpp"

#include <algorithm>          // std::for_each
#include <fstream>            // std::ifstream
#include <iostream>           // std::cout, std::endl (Please remove this for a better logger).

#define UNREFERENCED(x) (void)x

namespace Barrage
{

  // ==========================================================================
  // Resource IDs
  // ==========================================================================

  static const int INVALID_RESOURCE = -1;

  GfxManager2D::ResourceID::ResourceID() : ResourceID(INVALID_RESOURCE)
  {
  }

  GfxManager2D::ResourceID::ResourceID(int index) :
    internalResource_(new int(index)), objectsUsingThis_(new int(1))
  {
  }

  GfxManager2D::ResourceID::ResourceID(const ResourceID& rhs) :
    internalResource_(rhs.internalResource_), objectsUsingThis_(rhs.objectsUsingThis_)
  {
    ++* objectsUsingThis_;
  }

  GfxManager2D::ResourceID::~ResourceID()
  {
    Invalidate();
  }

  GfxManager2D::ResourceID& GfxManager2D::ResourceID::operator=(const ResourceID& rhs)
  {
    Invalidate();
    // Copy over the pointers to the new resource.
    objectsUsingThis_ = rhs.objectsUsingThis_;
    internalResource_ = rhs.internalResource_;
    // Increase the reference pointer.
    ++* objectsUsingThis_;
    // Return a reference to the assignee.
    return *this;
  }

  GfxManager2D::ResourceID::operator int() const
  {
    // Just dereference the pointer pointing to the index into the resource.
    return *internalResource_;
  }

  int GfxManager2D::ResourceID::RefCount() const
  {
    return *objectsUsingThis_;
  }

  void GfxManager2D::ResourceID::Invalidate()
  {
    // Decrease the pointer to the reference.
    if (objectsUsingThis_)
    {
      --* objectsUsingThis_;
      // If no one is using this resource after copying then we invalidate.
      if (*objectsUsingThis_ == 0)
      {
        delete objectsUsingThis_;
        delete internalResource_;
        // Make sure to clean up the pointers in debug mode.
        // Just to make sure we at least know of any improper 
        // uses of these resources involving their deletion.
        //#if defined(DEBUG) || defined(_DEBUG)
        //#endif
      }
      objectsUsingThis_ = nullptr;
      internalResource_ = nullptr;
    }
  }

  bool GfxManager2D::ResourceID::IsValid() const
  {
    return *internalResource_ != INVALID_RESOURCE;
  }

  // ==========================================================================
  // GfxManager2D
  // ==========================================================================

  GfxManager2D::GfxManager2D() :
    glVersion_(0), windowing_(nullptr)
  {
  }

  GfxManager2D::~GfxManager2D()
  {
    Shutdown();
  }

  void GfxManager2D::Initialize(WindowManager& windowing)
  {
    windowing_ = &windowing;
    /* Make the window's context current */
    glfwMakeContextCurrent(windowing.GetInternalHandle());
    /* Initialize the modern OpenGL functions using the context. */
    glVersion_ = gladLoadGL(glfwGetProcAddress);
    // Check we can use OpenGL.
    assert(glVersion_);
    // TODO: Replace this with a proper logger message.
    std::cout << "Loading OpenGL Version " << GLAD_VERSION_MAJOR(glVersion_) << "." << GLAD_VERSION_MINOR(glVersion_) << std::endl;
  }

  void GfxManager2D::Shutdown()
  {
    CleanAllResources();
  }
  
  GfxManager2D::MeshID GfxManager2D::CreateMesh(const MeshSpecs& specs)
  {
    // Create an empty mesh.
    MeshID mesh = CreateMesh();

    // Set the number of faces.
    internalMeshes_[mesh].faceCount_ = static_cast<int>(specs.indicesLength_);
    internalMeshes_[mesh].vertexCount_ = static_cast<int>(specs.bufferLength_);
    // Load the vertex buffer and its data from the specs.
    GfxManager2D::BufferList& buffers = meshBuffers_[mesh];
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, buffers[MeshBuffer::VERTICES]) );
    CHECK_GL( glBufferData(GL_ARRAY_BUFFER, specs.bufferLength_ * specs.bufferElementSize_, specs.buffer_, GL_STATIC_DRAW) );
    // Load the face buffer and its data from the specifications.
    CHECK_GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[MeshBuffer::FACES]) );
    CHECK_GL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, specs.indicesLength_ * specs.indicesElementSize_, specs.indices_, GL_STATIC_DRAW) );
    // Unbind all the buffers after their creation.
    CHECK_GL( glBindBuffer(GL_ARRAY_BUFFER, 0));
    CHECK_GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    return mesh;
  }

  GfxManager2D::TextureID GfxManager2D::CreateTexture(const TextureSpecs& specs)
  {
    // Create an empty texture.
    TextureID textureID = CreateTexture();
    TextureData& textureData = internalTextures_[textureID];
    // Bind the texture to the pipeline to start modifying it.
    GLuint texture = internalTextures_[textureID].internalTextureID_;
    // Find the OpenGL texture format and its usage.
    GLenum format = 0;
    GLenum usage = 0;
    GLenum filter = 0;

    switch (specs.format_)
    {
    case R8:
      format = GL_R8;
      usage = GL_RED;
      break;
    case R8G8:
      format = GL_RG8;
      usage = GL_RG;
      break;
    case R8G8B8:
      format = GL_RGB8;
      usage = GL_RGB;
      break;
    case R8G8B8A8:
    default:
      format = GL_RGBA8;
      usage = GL_RGBA;
    }
    // Create a texture with correct number of dimensions.
    GLenum textureType;
    switch (specs.dimensions_)
    {
    case 1:
      textureType = GL_TEXTURE_1D;
      CHECK_GL( glBindTexture(GL_TEXTURE_1D, texture) );
      CHECK_GL( glTexImage1D(GL_TEXTURE_1D, 0, format, specs.width_, 0, usage, GL_UNSIGNED_BYTE, specs.pixels_) );
      break;
    case 2:
    default:
      textureType = GL_TEXTURE_2D;
      CHECK_GL( glBindTexture(GL_TEXTURE_2D, texture) );
      CHECK_GL( glTexImage2D(GL_TEXTURE_2D, 0, format, specs.width_, specs.height_, 0, usage, GL_UNSIGNED_BYTE, specs.pixels_) );
      break;
    }
    // Set the filter.
    switch (specs.filter_)
    {
    case FILTER_NONE:
      filter = GL_NEAREST;
      break;
    case FILTER_LINEAR:
      filter = GL_LINEAR;
      break;
    }
    // Set the texture type internally.
    textureData.textureType_ = textureType;
    // Generate the mipmaps if needed.
    if (specs.createMipmaps_)
    {
      CHECK_GL( glGenerateMipmap(textureType) );
    }
    // Set the filtering options.
    CHECK_GL( glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter) );
    CHECK_GL( glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter) );

    // Unbind the texture created.
    CHECK_GL( glBindTexture(textureType, 0) );
    // Return the ID for the texture.
    return textureID;
  }

  GfxManager2D::FramebufferID GfxManager2D::CreateFramebuffer(const FramebufferSpecs& specs)
  {
    UNREFERENCED(specs);
    return FramebufferID(-1);
  }

  GfxManager2D::ShaderID GfxManager2D::CreateShader(const ShaderSpecs& specs)
  {
    // Create an empty shader.
    ShaderID shader = CreateShader();
    // The info log used for error checking.
    GLchar info[256];
    // To keep track of successes of operations on the shaders.
    int success;

    // Generate the shader code and create the code.
    StageList& stages = internalStages_[shader];
    GLuint& vertexShader = stages[ShaderStage::VERTEX_SHADER];

    // Set the vertex shader's source code and compile it.
    CHECK_GL( glShaderSource(vertexShader, 1, &specs.stageSources_[ShaderStage::VERTEX_SHADER], nullptr) );
    CHECK_GL( glCompileShader(vertexShader) );
    CHECK_GL( glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success) );
    if (!success)
    {
      CHECK_GL( glGetShaderInfoLog(vertexShader, sizeof(info) / sizeof(*info), nullptr, info) );
      std::cout << info << std::endl;
    }

    // Set the fragment shader's souruce code and compile it.
    GLuint& fragmentShader = stages[ShaderStage::PIXEL_SHADER];
    CHECK_GL( glShaderSource(fragmentShader, 1, &specs.stageSources_[ShaderStage::PIXEL_SHADER], nullptr) );
    CHECK_GL( glCompileShader(fragmentShader) );
    if (!success)
    {
      CHECK_GL( glGetShaderInfoLog(vertexShader, sizeof(info) / sizeof(*info), nullptr, info) );
      std::cout << info << std::endl;
    }

    // Generate the program and link the shaders.
    GLuint& program = internalPrograms_[shader];
    CHECK_GL( glAttachShader(program, vertexShader) );
    CHECK_GL( glAttachShader(program, fragmentShader) );
    CHECK_GL( glLinkProgram(program) );

    CHECK_GL( glGetProgramiv(program, GL_LINK_STATUS, &success) );
    if (!success)
    {
      CHECK_GL( glGetProgramInfoLog(program, sizeof(info) / sizeof(*info), nullptr, info) );
      std::cout << info << std::endl;
    }

    return shader;
  }

  GfxManager2D::MeshID GfxManager2D::CreateMesh()
  {
    // Create the mesh
    MeshData meshData = {};
    meshData.faceCount_ = 0;
    meshData.vertexCount_ = 0;
    // Create the buffers associated with the vertex array.
    BufferList buffers = {};
    CHECK_GL( glGenBuffers(NUM_BUFFERS, buffers.data()) );
    // Push back the resulting vertex array and the bufferse
    // that would go with it.
    meshBuffers_.push_back(buffers);
    internalMeshes_.push_back(meshData);
    // The mesh to keep track of indices correctly by indexing to the back.
    MeshID meshID(static_cast<int>(internalMeshes_.size()) - 1);
    meshes_.push_back(meshID);

    return meshID;
  }

  GfxManager2D::TextureID GfxManager2D::CreateTexture()
  {
    // Generate the ID to OpenGL to create an empty texture.
    GLuint texture = static_cast<GLuint>(-1);
    CHECK_GL( glGenTextures(1, &texture) );
    // Add the texture ID to the array and add the smart pointer.
    internalTextures_.push_back({ texture, 0 });
    TextureID textureID(static_cast<int>(internalTextures_.size()) - 1);
    textures_.push_back(textureID);
    // Return the ID to the texture.
    return textureID;
  }

  GfxManager2D::FramebufferID GfxManager2D::CreateFramebuffer()
  {
    return FramebufferID();
  }

  GfxManager2D::ShaderID GfxManager2D::CreateShader()
  {
    // First create the program and the shader objects associated with it.
    GLuint program = glCreateProgram();
    CHECK_GL((void)0);
    StageList list = {
      glCreateShader(GL_VERTEX_SHADER),
      glCreateShader(GL_FRAGMENT_SHADER),
    };
    CHECK_GL((void)0);
    // Add the objects in.
    internalPrograms_.push_back(program);
    internalStages_.push_back(list);
    // Create the smart pointer that will keep track of the resources.
    ShaderID shaderID(static_cast<int>(internalPrograms_.size() - 1));
    shaderPrograms_.push_back(shaderID);

    return shaderID;
  }

  void GfxManager2D::CleanUnusedResources()
  {
    // Clean up unused meshes.
    // Check that all the lists here are the same size.
    const size_t meshListSize = internalMeshes_.size();
    UNREFERENCED(meshListSize);
    assert(meshBuffers_.size() == meshListSize);
    assert(meshes_.size() == meshListSize);
    CleanUnusedInList(meshes_, &GfxManager2D::CleanUnusedMeshes);

    // Clean up unused shaders.
    // Check that all the resources are indeed the same size.
    const size_t programListSize = internalPrograms_.size();
    UNREFERENCED(programListSize);
    assert(internalStages_.size() == programListSize);
    assert(shaderPrograms_.size() == programListSize);
    CleanUnusedInList(shaderPrograms_, &GfxManager2D::CleanUnusedShaders);

    // Clean up unused textures.
    // Check that all the resources are indeed the same size.
    const size_t textureListSize = internalTextures_.size();
    UNREFERENCED(textureListSize);
    assert(textures_.size() == textureListSize);
    CleanUnusedInList(textures_, &GfxManager2D::CleanUnusedTextures);
    
    // TODO: Clean up framebuffers.
  }

  void GfxManager2D::CleanAllResources()
  {
    // This function is in charge of invalidating
    // the resources.
    /*
    auto invalidation = [](ResourceID& resource)
    {
      resource.Invalidate();
    };
    // Clean up the smart pointers.
    std::for_each(meshes_.begin(), meshes_.end(), invalidation);
    std::for_each(shaderPrograms_.begin(), shaderPrograms_.end(), invalidation);
    std::for_each(textures_.begin(), textures_.end(), invalidation);
    std::for_each(framebuffers_.begin(), framebuffers_.end(), invalidation);
    */
    // Made sure to clear all bad pointers to the resources.
    meshes_.clear();
    shaderPrograms_.clear();
    textures_.clear();
    framebuffers_.clear();

    // Clean up the OpenGL resources.

    // Clean up the vertex array and its buffers
    for (BufferList& vbo : meshBuffers_)
    {
      CHECK_GL( glDeleteBuffers(NUM_BUFFERS, &vbo[0]) );
    }
    /*
    for (MeshData& vao : internalMeshes_)
    {
      CHECK_GL( glDeleteVertexArrays(1, &vao.internalMeshID_) );
    }
    */
    // Clean up all the textures.
    for (TextureData& texture : internalTextures_)
    {
      CHECK_GL( glDeleteTextures(1, &texture.internalTextureID_) );
    }
    // Clean up all the shaders and their stages.
    for (GLuint& program : internalPrograms_)
    {
      CHECK_GL( glDeleteProgram(program) );
    }
    for (StageList& list : internalStages_)
    {
      for (GLuint& stage : list)
      {
        CHECK_GL( glDeleteShader(stage) );
      }
    }
    // Clean up all the framebuffers.
    for (GLuint& framebuffer : internalFramebuffers_)
    {
      CHECK_GL( glDeleteFramebuffers(1, &framebuffer) );
    }

    // AND... clear all useless resources borrowed from OpenGL.
    meshBuffers_.clear();
    internalMeshes_.clear();
    internalTextures_.clear();
    internalPrograms_.clear();
    internalStages_.clear();
    internalFramebuffers_.clear();
  }

  void GfxManager2D::FlipWindowBuffers()
  {
    assert(windowing_);
    windowing_->FlipWindowBuffers();
  }

  const std::vector<GfxManager2D::MeshID>& GfxManager2D::GetMeshes() const
  {
    return meshes_;
  }

  const std::vector<GfxManager2D::TextureID>& GfxManager2D::GetTextures() const
  {
    return textures_;
  }

  const std::vector<GfxManager2D::FramebufferID>& GfxManager2D::GetFramebuffers() const
  {
    return framebuffers_;
  }

  const std::vector<GfxManager2D::ShaderID>& GfxManager2D::GetShaders() const
  {
    return shaderPrograms_;
  }

  const std::vector<GfxManager2D::MeshData>& GfxManager2D::GetOpenGLMeshes() const
  {
    return internalMeshes_;
  }

  const std::vector<GfxManager2D::BufferList>& GfxManager2D::GetOpenGLBuffers() const
  {
    return meshBuffers_;
  }

  const std::vector<GfxManager2D::TextureData>& GfxManager2D::GetOpenGLTextures() const
  {
    return internalTextures_;
  }

  const std::vector<GLuint>& GfxManager2D::GetOpenGLFramebuffers() const
  {
    return internalFramebuffers_;
  }

  const std::vector<GLuint>& GfxManager2D::GetOpenGLShaders() const
  {
    return internalPrograms_;
  }

  const std::vector<GfxManager2D::StageList>& GfxManager2D::GetOpenGLShaderStages() const
  {
    return internalStages_;
  }

  const WindowManager* GfxManager2D::GetInternalWindow() const
  {
    return windowing_;
  }

  WindowManager* GfxManager2D::GetInternalWindow()
  {
    return windowing_;
  }

  void GfxManager2D::CleanUnusedInList(std::vector<ResourceID>& resourceList, void (GfxManager2D::* cleanExtension)(size_t))
  {
    for (size_t i = 0; i < resourceList.size(); )
    {
      // The flag that marks whether there was a 
      // swap (deletion of a resource).
      bool swapped = false;
      // Check the resource isn't being used anymore.
      const ResourceID& id = resourceList[i];
      if (id.RefCount() == 1)
      {
        // At this point no one is using the resource and it must 
        // removed.

        // Swap the resources with the last element on the back AND pop the back.
        std::swap(resourceList[i], resourceList.back());
        // Call the extension function for anything else that needs to get done.
        (this->*cleanExtension)(i);
        // If the popped element was the one on the back
        // then we don't have to change anything... it's already gone.
        // Otherwise, we have to read just the index the resource
        // points to.
        // TODO: Figure out a better way of doing this, maybe with an assert?
        *(resourceList[i].internalResource_) = static_cast<int>(i);
        // Eliminate the smart pointer and it's now defunct resources.
        // We do it after setting the resource (even if it's deleted)
        // beacuse it makes the algorithm less complex.
        // And the time the resource gets removed doesn't really matter.
        resourceList.pop_back();
        // Mark the swapped flag so we don't advance past another resource that needs
        // checking.
        swapped = true;
      }
      // If there was a swap then we don't advance, we need to examine 
      // this resource before moving on.
      if (!swapped)
      {
        ++i;
      }
    }
  }

  void GfxManager2D::CleanUnusedMeshes(size_t i)
  {
    // Make sure to move all the resources to the correct place.
    std::swap(meshBuffers_[i], meshBuffers_.back());
    std::swap(internalMeshes_[i], internalMeshes_.back());
    // Clear the OpenGL resources associated with clearing a mesh.
    CHECK_GL( glDeleteBuffers(NUM_BUFFERS, meshBuffers_.back().data()) );
    /*
    CHECK_GL( glDeleteVertexArrays(1, &internalMeshes_.back().internalMeshID_) );
    */
    // Kick out the bucket with the old resources.
    meshBuffers_.pop_back();
    internalMeshes_.pop_back();
  }

  void GfxManager2D::CleanUnusedTextures(size_t i)
  {
    // Swap the resources with the last element on the back AND pop the back.
    std::swap(internalTextures_[i], internalTextures_.back());
    // Clear the OpenGL resources associated with clearing a shader program.
    CHECK_GL( glDeleteTextures(1, &internalTextures_.back().internalTextureID_) );
    // Eliminate the smart pointer and it's now defunct resources.
    internalTextures_.pop_back();
  }

  void GfxManager2D::CleanUnusedShaders(size_t i)
  {
    // Swap the resources with the last element on the back AND pop the back.
    std::swap(internalStages_[i], internalStages_.back());
    std::swap(internalPrograms_[i], internalPrograms_.back());
    // Clear the OpenGL resources associated with clearing a shader program.
    const GLuint* shaderBuffer = internalStages_.back().data();
    std::for_each(shaderBuffer, shaderBuffer + ShaderStage::NUM_SHADERS_POSSIBLE, glDeleteShader);
    CHECK_GL((void)0);
    CHECK_GL( glDeleteProgram(internalPrograms_.back()) );
    // Eliminate the now defunct resources.
    internalStages_.pop_back();
    internalPrograms_.pop_back();
  }
}
