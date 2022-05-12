/* ========================================================================= */
/*!
 *
 * \file            GfxDraw2D.hpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Defines a simplified interface that manages the renderer.
 * The interface becomes nicer and whatnot.
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef GfxDraw2D_MODULE_H
#define GfxDraw2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include "GfxManager2D.hpp"
#include "GfxRenderer2D.hpp"

namespace Barrage
{
  class GfxRenderer2D;

  class GfxDraw2D //! Creates a nicer interface to render anything.
  {
  public:

    /*************************************************************************/
    /*!
      \brief
        Creates a system that simplifies the drawing process
    */
    /*************************************************************************/
    explicit GfxDraw2D();
    /*************************************************************************/
    /*!
      \brief
        Initializes the system by selecting the renderer being used.
      \param manager
        The manager to create internal resources with.
      \param renderer
        The renderer that keeps track of all the commands sent to it.
    */
    /*************************************************************************/
    void Initialize(GfxManager2D& manager, GfxRenderer2D& renderer);

    /*************************************************************************/
    /*!
      \brief
        Draws a square with the given parameters.
      \param position
        The position to draw the square in.
      \param scale
        The scale to draw the square in.
      \param rotation
        The rotation to draw the square in.
      \param texture
        The texture to apply to the square.
    */
    /*************************************************************************/
    void DrawQuad(
      const glm::vec2& position, const glm::vec2& scale, const RADIAN& rotation,
      const GfxManager2D::TextureID& texture = GfxManager2D::TextureID()
    );
    /*************************************************************************/
    /*!
      \brief
        Draws several squares with the given parameters.
      \param count
        The number of elements being rendered.
      \param positions
        The position to draw the square in.
      \param scales
        The scale to draw the square in.
      \param rotations
        The rotation to draw the square in.
      \param texture
        The texture to apply to the square.
    */
    /*************************************************************************/
    void DrawInstancedQuad(
      int count,
      const glm::vec2* positions,
      const glm::vec2* scales,
      const RADIAN* rotations,
      const GfxManager2D::TextureID& texture = GfxManager2D::TextureID()
    );
    /*************************************************************************/
    /*!
      \brief
        Applies a shader effect for any shapes drawn after this call.
      \param shader
        The shader to apply to all shapes after the fact.
    */
    /*************************************************************************/
    void ApplyShader(const GfxManager2D::ShaderID& shader);
    /*************************************************************************/
    /*!
      \brief
        Binds a framebuffer to the pipeline. Any shapes drawn will now
        be drawn to the current framebuffer.
      \param framebuffer
        The framebuffer to render everything to.
    */
    /*************************************************************************/
    void ApplyFramebuffer(const GfxManager2D::FramebufferID& framebuffer);

  private:
    GfxManager2D::ShaderID boundShader_;            //!< The currently bound shader.
    GfxManager2D::FramebufferID boundFrame_;        //!< The currently bound framebuffer.
    GfxManager2D::MeshID quad_;                     //!< The square mesh rendered.
    GfxManager2D* manager_;                         //!< The internal manager to create internal resources with.
    GfxRenderer2D* renderer_;                       //!< The internal renderer which keeps track of the commands sent to it.
    std::vector<glm::vec2> singlePositions_;        //!< The buffer to store single call positions.
    std::vector<glm::vec2> singleScales_;           //!< The buffer to store single call scales.
    std::vector<float> singleRotations_;            //!< The buffer to store single rotations.
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GfxDraw2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////