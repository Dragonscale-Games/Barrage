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
      \param renderer
        The renderer that keeps track of all the commands sent to it.
    */
    /*************************************************************************/
    void Initialize(GfxRenderer2D* renderer);

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
      \param textureID
        The texture to apply to the square.
    */
    /*************************************************************************/
    void DrawSquare(
      const glm::vec2& position, const glm::vec2& scale, const RADIAN& rotation,
      const GfxManager2D::TextureID& textureID);
    /*************************************************************************/
    /*!
      \brief
        Draws several squares with the given parameters.
      \param instanced
        Whether the 
      \param count
        The number of elements being rendered.
      \param positions
        The position to draw the square in.
      \param scales
        The scale to draw the square in.
      \param rotations
        The rotation to draw the square in.
      \param textureID
        The texture to apply to the square.
    */
    /*************************************************************************/
    void DrawSeveralSquares(
      bool instanced,
      int count,
      const glm::vec2& positions,
      const glm::vec2& scales,
      const RADIAN& rotations,
      const GfxManager2D::TextureID& textureID
    );
    /*************************************************************************/
    /*!
      \brief
        Applies a shader effect for any shapes drawn after this call.
      \param shaderID
        The shader to apply to all shapes after the fact.
    */
    /*************************************************************************/
    void ApplyShader(const GfxManager2D::ShaderID& shaderID);
    /*************************************************************************/
    /*!
      \brief
        Binds a framebuffer to the pipeline. Any shapes drawn will now
        be drawn to the current framebuffer.
    */
    /*************************************************************************/
    void ApplyFramebuffer(const GfxManager2D::FramebufferID& framebufferID);

  private:
    GfxRenderer2D* renderer_;                       //!< The internal renderer which keeps track of the commands sent to it.
    const GfxManager2D::ShaderID* boundShader;      //!< The currently bound shader.
    const GfxManager2D::FramebufferID* boundFrame;  //!< The currently bound framebuffer.
    GfxManager2D::MeshID square_;                   //!< The square mesh rendered.
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GfxDraw2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////