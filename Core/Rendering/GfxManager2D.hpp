/* ========================================================================= */
/*!
 *
 * \file            GfxManager2D.hpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Defines the interface used to initialize all graphics.
 * Responsible with creating the context for the window and managing
 * all the resources used to render anything to the screen (e.g. shaders,
 * meshes, framebuffer).
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef GfxManager2D_MODULE_H
#define GfxManager2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================

#include <glad/gl.h>
#include <vector>
#include <array>
#include "GfxTypes.hpp"

namespace Barrage
{
  class WindowManager; //!< Forward declaration to the window system.

  /***************************************************************************/
  /*!
    \brief
      This manager manages all the resources needed for rendering to a 
      single window.
      - The manager is in charge of creating and deleting the window's rendering
      context.
      - The manager is in charge of managing and delivering the resources
      for the graphics api.
  */
  /***************************************************************************/
  class GfxManager2D
  {
  public:
    
    /*************************************************************************/
    /*!
      \brief
        The ResourceID abstracts the internal ID away from the user.
        When meshes get deleted the IDs may get switched in order to
        increase performance, therefore, it is important to have a way
        to automagically do that for the users.

        When no users are using this Resource ID, then the system
        will take care of the deleting the mesh.
    */
    /*************************************************************************/
    class ResourceID
    {
    public:
      /***********************************************************************/
      /*!
        \brief
          Create an empty resource.
      */
      /***********************************************************************/
      ResourceID();
      /***********************************************************************/
      /*!
        \brief
          The original resource id that this is copying from.
        \param rhs
          The object this is making a copy out of.
      */
      /***********************************************************************/
      ResourceID(const ResourceID& rhs);
      /***********************************************************************/
      /*!
        \brief
          Assigns a resource ID into another.
        \param rhs
          The resouce copying over the ID from.
      */
      /***********************************************************************/
      ResourceID& operator=(const ResourceID& rhs);
      /***********************************************************************/
      /*!
        \brief
          When the resource gets destructed then the "smart pointer"
          will take care of managing the OpenGL resource.
      */
      /***********************************************************************/
      ~ResourceID();
      /***********************************************************************/
      /*!
        \brief
          Gets the correct ID for the internal mesh.
        \returns
          The internal mesh this resource points to.
      */
      /***********************************************************************/
      operator int() const;
      /***********************************************************************/
      /*!
        \brief
          Gets how many objects are pointing to this resource.
      */
      /***********************************************************************/
      int RefCount() const;
      /***********************************************************************/
      /*!
        \brief
          Causes this instance of the resource smart pointer
          to immediately delete any resources it uses
          to keep track of instances.
      */
      /***********************************************************************/
      void Invalidate();
      /***********************************************************************/
      /*!
        \brief
          Checks whether a resource is valid or not based on the
          reference index.
        \returns
          - True if the resource is a valid one.
          - False otherwise.
      */
      /***********************************************************************/
      bool IsValid() const;

    private:
      /***********************************************************************/
      /*!
        \brief
          Creates a smart class that keeps track into the index
          where the mesh is supposed to exist.
        \param index
          The index to the resource.
      */
      /***********************************************************************/
      ResourceID(int index);

      int* internalResource_;     //!< The index into the array to point to.
      int* objectsUsingThis_;     //!< The count of the number of resources pointing to this.

      friend class GfxManager2D;
    };

    typedef ResourceID MeshID;            //!< Typedef for the Mesh IDs.
    typedef ResourceID TextureID;         //!< Typedef for the Texture IDs.
    typedef ResourceID FramebufferID;     //!< Typedef for Framebuffer IDs.
    typedef ResourceID ShaderID;          //!< Typedef for the Shader IDs.

    struct MeshData //! Represents the mesh data needed to draw the meshes.
    {
      GLuint vertexCount_;    //!< The number of vertices this has.
      GLuint faceCount_;      //!< The number of faces the mesh has.
    };

    struct TextureData //! Represents the texture data needed to draw textures.
    {
      GLuint internalTextureID_; //!< The internal texture ID to OpenGL.
      GLenum textureType_;       //!< The OpenGL texture type.
    };

    struct MeshSpecs //! Represents the specifications for mesh creation.
    {
      size_t bufferLength_;
      size_t bufferElementSize_;
      size_t indicesLength_;
      size_t indicesElementSize_;
      const void* buffer_;
      const void* indices_;
    };

    enum ShaderStage //! Enumerates the available shader stages.
    {
      VERTEX_SHADER = 0,
      PIXEL_SHADER,
      // This one always goes last.
      NUM_SHADERS_POSSIBLE,
    };

    enum MeshBuffer //! Enumerates the available buffers written by this system.
    {
      VERTICES,
      // UVS,
      FACES,
      // This one always goes last.
      NUM_BUFFERS,
    };

    struct TextureSpecs //! Represents the specifications for the textures.
    {
      int width_;                       //!< The width of the mesh.
      int height_;                      //!< The height of the mesh.
      int dimensions_;                  //!< The number of dimensions the textures should have.
      bool createMipmaps_;              //!< Whether mipmaps should be created for this texture.
      TextureFormat format_;            //!< The format the pixels are arranged.
      TextureFilter filter_;            //!< The type of filter to apply to this texture.
      const unsigned char* pixels_;     //!< The pixels of the mesh.
    };

    struct ShaderSpecs //! Represents the specifications for the shaders used.
    {
      const char* stageSources_[ShaderStage::NUM_SHADERS_POSSIBLE]; //!< Used to specify the code for the shader stages available.
    };
    
    struct FramebufferSpecs //! Represents the specifications used for framebuffers.
    {
      TextureID depthStencilBuffer_;          //!< The depth stencil buffer.
      std::vector<TextureID> outputBuffers_;  //!< The buffers to use for the framebuffer.
    };

    typedef std::array<GLuint, ShaderStage::NUM_SHADERS_POSSIBLE> StageList; //!< The container for all the stages.
    typedef std::array<GLuint, MeshBuffer::NUM_BUFFERS> BufferList; //!< The container for all buffers per array.

  public:

    /*************************************************************************/
    /*!
      \brief
        Creates the graphics manager.
    */
    /*************************************************************************/
    GfxManager2D();
    /*************************************************************************/
    /*!
      \brief
        Cleans up after all the memory being used by this manager.
    */
    /*************************************************************************/
    ~GfxManager2D();

    /*************************************************************************/
    /*!
      \brief
        Initializes the graphics manager given the window it's supposed to manage.
      \param windowing
        The windowing system to manage.
    */
    /*************************************************************************/
    void Initialize(WindowManager& windowing);
    /*************************************************************************/
    /*!
      \brief
        Shuts down the system and cleans up all resources associated with
        it.
    */
    /*************************************************************************/
    void Shutdown();
    /*************************************************************************/
    /*!
      \brief
        Creates a single mesh given the vertices and indices for it.
      \param specs
        The specifications to create the mesh with.
      \returns
        The ID that points to the newly created mesh.
    */
    /*************************************************************************/
    MeshID CreateMesh(const MeshSpecs& specs);
    /*************************************************************************/
    /*!
      \brief
        Creates a texture given the width and height of the specified
        texture.
      \param specs
        The specifications to create the texture with.
      \returns
        The ID that points to created the texture.
    */
    /*************************************************************************/
    TextureID CreateTexture(const TextureSpecs& specs);
    /*************************************************************************/
    /*!
      \brief
        Creates a basic framebuffer given to the color textures to output to.
      \param specs
        The specifications to create the framebuffer with.
      \returns
        The ID that points to the created framebuffer.
    */
    /*************************************************************************/
    FramebufferID CreateFramebuffer(const FramebufferSpecs& specs);
    /*************************************************************************/
    /*!
      \brief
        Creates a shader given the source codes for each shader stage.
      \param specs
        The specifications to create the shader with.
      \returns
        The ID that points to the created shader.
    */
    /*************************************************************************/
    ShaderID CreateShader(const ShaderSpecs& specs);

    /*************************************************************************/
    /*!
      \brief
        Creates a newly-allocated (empty) mesh.
      \returns
        The ID to the newly-created mesh.
    */
    /*************************************************************************/
    MeshID CreateMesh();
    /*************************************************************************/
    /*!
      \brief
        Creates a newly-allocated (empty) texture.
      \returns
        The ID to the newly-created texture.
    */
    /*************************************************************************/
    TextureID CreateTexture();
    /*************************************************************************/
    /*!
      \brief
        Creates a newly-allocated (empty) framebuffer.
      \returns
        The ID to the newly-created framebuffer.
    */
    /*************************************************************************/
    FramebufferID CreateFramebuffer();
    /*************************************************************************/
    /*!
      \brief
        Creates a newly-allocated (empty) shader.
      \returns
        The ID to the newly-created shader.
    */
    /*************************************************************************/
    ShaderID CreateShader();
    /*************************************************************************/
    /*!
      \brief
        Cleans up the resources that do not any objects pointing to it.
    */
    /*************************************************************************/
    void CleanUnusedResources();
    /*************************************************************************/
    /*!
      \brief
        Cleans up all the resources regardless if they are being used
        or not.
        Preferably, use the CleanUnusedResources function.
    */
    /*************************************************************************/
    void CleanAllResources();

    /*************************************************************************/
    /*!
      \brief
        Gets the internal array of all the mesh IDs (read-only).
      \returns
        The internal array for all the mesh IDs.
    */
    /*************************************************************************/
    const std::vector<MeshID>& GetMeshes() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal array of all the IDs for the shaders (read-only).
      \returns
        The internal array for all the texture IDs.
    */
    /*************************************************************************/
    const std::vector<TextureID>& GetTextures() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal array for all the IDs for the framebuffers
        (read-only).
      \returns
        The internal array for all the framebuffer IDs.
    */
    /*************************************************************************/
    const std::vector<FramebufferID>& GetFramebuffers() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal array for all the IDs for the shaders.
      \returns
        The internal array for all the shader IDs.
    */
    /*************************************************************************/
    const std::vector<ShaderID>& GetShaders() const;

    /*************************************************************************/
    /*!
      \brief
        Gets the internal array of all the OpenGL meshes (read-only).
      \returns
        The internal array for all the mesh OpenGL pointers along with
        their face counts.
    */
    /*************************************************************************/
    const std::vector<MeshData>& GetOpenGLMeshes() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal array of all the mesh buffers (read-only).
      \returns
        The internal array for all the buffer pointers to their correspoding
        meshes.
    */
    /*************************************************************************/
    const std::vector<BufferList>& GetOpenGLBuffers() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal array of all the OpenGL textures.
      \returns
        The internal array for all the texture pointers.
    */
    /*************************************************************************/
    const std::vector<TextureData>& GetOpenGLTextures() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal array for all the OpenGL framebuffers
        (read-only).
      \returns
        The internal array for all the framebuffer pointers.
    */
    /*************************************************************************/
    const std::vector<GLuint>& GetOpenGLFramebuffers() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal array for all the OpenGL shaders.
      \returns
        The internal array for all the shader pointers.
    */
    /*************************************************************************/
    const std::vector<GLuint>& GetOpenGLShaders() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the shader stages each program uses.
      \returns
        The internal array for all shader stage IDs.
    */
    /*************************************************************************/
    const std::vector<StageList>& GetOpenGLShaderStages() const;

    /*************************************************************************/
    /*!
      \brief
        Gets a pointer to the windowing system this manager depends
        to create the context.
      \returns
        The pointer to the windowing system this manager manages for.
    */
    /*************************************************************************/
    WindowManager* GetInternalWindow();
    /*************************************************************************/
    /*!
      \brief
        Gets a pointer to the windowing system this manager depends
        to create the context.
      \returns
        The pointer to the windowing system this manager manages for.
    */
    /*************************************************************************/
    const WindowManager* GetInternalWindow() const;

  private:

    /*************************************************************************/
    /*!
      \brief
        Please do not make a copy out the manager. Implementing this would cost
        more trouble than its worth.
    */
    /*************************************************************************/
    GfxManager2D(const GfxManager2D&) = delete;
    /*************************************************************************/
    /*!
      \brief
        Please do not make a copy out the manager. Implementing this would cost
        more trouble than its worth.
    */
    /*************************************************************************/
    void operator=(const GfxManager2D&) = delete;
    /*************************************************************************/
    /*!
      \brief
        Cleans up the resource list based on the resource reference count
        and lets the caller do anything else that's needed
        that is specififc to that resource.
      \param resourceList
        The resource list that is getting cleaned.
      \param cleanExtension
        A function pointer that takes the index at which the resource
        was cleaned so the caller can do anything else that's needed.
    */
    /*************************************************************************/
    void CleanUnusedInList(std::vector<ResourceID>& resourceList, void (GfxManager2D::*cleanExtension)(size_t));
    /*************************************************************************/
    /*!
      \brief
        Cleans up the resources for the meshes.
      \param index
        The index where the resources got deleted from.
    */
    /*************************************************************************/
    void CleanUnusedMeshes(size_t index);
    /*************************************************************************/
    /*!
      \brief
        Cleans up the resources for the meshes.
      \param index
        The index where the resources got deleted from.
    */
    /*************************************************************************/
    void CleanUnusedTextures(size_t index);
    /*************************************************************************/
    /*!
      \brief
        Cleans up the resources for the meshes.
      \param index
        The index where the resources got deleted from.
    */
    /*************************************************************************/
    void CleanUnusedShaders(size_t index);

    int glVersion_;                                                   //!< Store the version of OpenGL used.
    WindowManager* windowing_;                                        //!< The windowing system to create the context for.

    std::vector<MeshData> internalMeshes_;                            //!< Holds the interal rendering meshes.
    std::vector<BufferList> meshBuffers_;                             //!< The buffers for the meshes (that are managed by this system).
    std::vector<MeshID> meshes_;                                      //!< Keeps of how many resources point to the meshes.

    std::vector<TextureData> internalTextures_;                       //!< Keeps track of the internal textures.
    std::vector<TextureID> textures_;                                 //!< The textures used to render.

    std::vector<GLuint> internalPrograms_;                            //!< Keeps track of the internal programs.
    std::vector<StageList> internalStages_;                           //!< Keeps track of the internal shaders.
    std::vector<ShaderID> shaderPrograms_;                            //!< The shader programs used.

    std::vector<GLuint> internalFramebuffers_;                        //!< Keeps track of the internal framebuffers.
    std::vector<FramebufferID> framebuffers_;                         //!< The target framebuffers used.
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GfxManager2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////
