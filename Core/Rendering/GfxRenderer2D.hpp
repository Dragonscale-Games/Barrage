/* ========================================================================= */
/*!
 *
 * \file            GfxManager2D.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used to initialize all graphics.
 * Responsible with creating the context for the window and managing
 * all the resources used to render anything to the screen (e.g. shaders,
 * meshes, framebuffer).
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef GfxRenderer2D_MODULE_H
#define GfxRenderer2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////

  //  ===========================================================================
  // Includes
  //  ===========================================================================

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <Utilities/Utilities.hpp>
#include "GfxManager2D.hpp"

namespace Barrage
{
  class GfxManager2D; //!< Forward declaration for the graphics manager.

  class GfxRenderer2D
  {
  public:

    struct TransformData //! The transform data needed for either type of request.
    {
      int count_;                       //!< The count of all the positions.
      const glm::vec2* positions_;      //!< The positions to all the objects in the render the request.
      const glm::vec2* scales_;         //!< The scales to all the objects in the render the request.
      const glm::mat2x2* uvMaps_;       //!< The uv maps to all objects in the request.
      const RADIAN* rotations_;         //!< The rotations to all the objects in the request.
      const glm::vec4* texCoords_;      //!< The texture coordinates of all objects in the request.
    };

    struct ResourceState //!< Keeps track of the currently bound resources.
    {
      GfxManager2D::MeshID mesh_;                 //!< The currently bound mesh.
      GfxManager2D::TextureID texture_;           //!< The currently bound texture.
      GfxManager2D::ShaderID shader_;             //!< The currently bound shader.
      GfxManager2D::FramebufferID framebuffer_;   //!< The currently bound framebuffer.
    };

    struct InstancedRequest //! The structure to keep track of instanced requests.
    {
      ResourceState resources_;           //!< The resources used on this binding.
      TransformData transform_;           //!< The transform data for the instance request.
    };

    struct InternalState //! The internal request data where the pointer data is already dereferenced.
    {
      int meshIndex_;         //!< The index to the internal mesh in the resources manager.
      int textureIndex_;      //!< The index to the internal texture in the resources manager.
      int shaderIndex_;       //!< The index to the internal shader in the resources manager.
      int framebufferIndex_;  //!< The index to the internal framebuffer in the resources manager.
    };

    struct InternalRequest //! The internal data for the single requests.
    {
      InternalState resources_; //!< The manager resources needed for this request.
      TransformData transform_; //!< The transform data for this request.
    };

  public:
    /*************************************************************************/
    /*!
      \brief
        Creates the renderer and sets sets it on a working state.
    */
    /*************************************************************************/
    GfxRenderer2D();
    /*************************************************************************/
    /*!
      \brief
        Initializes the graphics renderer using the manager to get
        the resources from.
      \param manager
        The manager this renderer will get the resources from.
    */
    /*************************************************************************/
    void Initialize(GfxManager2D& manager);
    /*************************************************************************/
    /*!
      \brief
        Mainly clears the buffers needed for the instanced mesh and
        clears all requests still stored.
    */
    /*************************************************************************/
    void Shutdown();

    /*************************************************************************/
    /*!
      \brief
        The number of requests expected out of this renderer per frame.
        This may allocate: 
        requests * (sizeof(RenderRequest) + sizeof(InstancedRequests)
        bytes from the heap if there isn't enough space already.
      \param requests
        The number of requests expected from the renderer.
    */
    /*************************************************************************/
    void SetExpectedRequests(size_t requests);
    /*************************************************************************/
    /*!
      \brief
        Sets the color to clear the screen.
      \param color
        The the color to clear the screen with.
    */
    /*************************************************************************/
    void SetBackgroundColor(const glm::vec4& color);
    /*************************************************************************/
    /*!
      \brief
        Sets the renderer's viewport width and height.
        This sets the projection matrix to set the available rendered
        space to the normalized device coordinates.
      \param dimensions
        The width and height in pixels the renderer
        has available to render.
      \param origin
        The lower left corner of the rendering surface.
    */
    /*************************************************************************/
    void SetViewportSpace(const glm::ivec2& dimensions, const glm::ivec2& origin = glm::ivec2(0,0));
    /*************************************************************************/
    /*!
      \brief
        Sets the camera's transform in the renderer itself.
      \remarks
        This function rebuilds the camera matrix from scratch every call.
      \param position
        The position of the camera in world coordiantes.
      \param zoom
        The zoom factor which scales the world.
      \param rotation
    */
    /*************************************************************************/
    void SetCameraTransform(const glm::vec2& position, float zoom, RADIAN rotation);
    
    /*************************************************************************/
    /*!
      \brief
        Adds the rendering request to the internal structure
        the renderer uses to keep track of where everything is needed.
      \param request
        The rendering request made to the renderer.
        The renderer assumes the pointers are still valid by the point
        the commands get renderered, there is no safety check to make
        sure everything is OK.
    */
    /*************************************************************************/
    void AddRequest(const InstancedRequest& request);
    /*************************************************************************/
    /*!
      \brief
        Renders all of condensed requests to the screen.
    */
    /*************************************************************************/
    void RenderRequests();
    /*************************************************************************/
    /*!
      \brief
        Flushes all the requests (both condensed and not) and swaps
        the back buffers of the window.
    */
    /*************************************************************************/
    void FlushRequests();
    /*************************************************************************/
    /*!
      \brief
        Clears the framebuffer.
    */
    /*************************************************************************/
    void ClearFramebuffer();

    /*************************************************************************/
    /*!
      \brief
        Gets the color used for clearing the screen.
      \returns
        A reference to the color used to clear the screen.
    */
    /*************************************************************************/
    const glm::vec4& GetBackgroundColor() const;
    
  private:

    struct ConstantBuffer //! A structure used to maintain the data about the viewport.
    {
      glm::mat4 projection_; //!< The projection matrix of the renderer's viewport.
      glm::mat4 camera_;     //!< The matrix to the canonical camera space.
    };
    
    /*************************************************************************/
    /*!
      \brief
        Helper function to create the internal instanced mesh.
        Not smart and won't cleanup resources.
    */
    /*************************************************************************/
    void CreateInstancedMesh();
    /*************************************************************************/
    /*!
      \brief
        Renders an instanced request using the internal instanced mesh.
      \param manager
        The manager that keeps track of the resources for OpenGL.
      \param shaderID
        The shader ID to OpenGL that is currently bound to the pipeline.
      \param meshData
        The data from the mesh being requested to render.
      \param request
        A C-style polymorphic struct containing the data needed to know
        what resources are being used but if use correctly should
        also be casted to whatever type is expected to make this work.
    */
    /*************************************************************************/
    void RenderInstancedMesh(
      const GLuint shaderID, 
      const GfxManager2D::MeshData& meshData, 
      const InternalRequest& request,
      const GfxManager2D* manager);
    /*************************************************************************/
    /*!
      \brief
        Binds the buffers responsible for the mesh data.
      \param buffers
        The buffers to bind to this renderer.
    */
    /*************************************************************************/
    static void BindMeshBuffers(const GfxManager2D::BufferList& buffers);
    
    enum InstancedBuffer //! The indices to the instanced buffers.
    {
      TRANSLATION_BUFFER,
      SCALE_BUFFER,
      ROTATION_BUFFER,
      TEXCOORD_BUFFER,
      BUFFER_COUNT
    };

    GLuint renderState_;                      //!< The vertex array object for the renderer.
    glm::vec4 clearColor_;                    //!< The color to clear the screen.
    ConstantBuffer constants_;                //!< The viewport for this renderer.
    InternalState current_;                   //!< The current resource state.
    GfxManager2D* manager_;                   //!< The graphics manager rendering everything for.
    GfxManager2D::MeshID instancedMesh_;      //!< The mesh used to render everything instanced.
    GLuint instancedBuffers_[BUFFER_COUNT];   //!< The buffers needed for the instanced mesh.
    std::vector<InternalRequest> requests_;   //!< The internal requests stored for rendering in order.
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GfxRenderer2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////
