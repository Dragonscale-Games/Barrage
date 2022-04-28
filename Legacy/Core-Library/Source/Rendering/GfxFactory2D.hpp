/* ========================================================================= */
/*!
 *
 * \file            GfxFactory2D.hpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Makes creating any of the resources easier and data driven.
 * 
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef GfxFactory2D_MODULE_H
#define GfxFactory2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include "GfxManager2D.hpp"

namespace Barrage
{
  class GfxFactory2D //! Creates an interface to create gfx resources data driven.
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Creates a system that simplifies the resource creation process.
      \param manager
        The manager in charge of creating all the resources.
    */
    /*************************************************************************/
    explicit GfxFactory2D(GfxManager2D* manager);

    /*************************************************************************/
    /*!
      \brief
        Creates a shader given the filenames of the shader starting
        from the current directory.
      \param filepaths
        The filepaths of each shader for the program created.
        The index into the array corresponds to the enumeration
        for the shader stages in GfxManager2D.
    */
    /*************************************************************************/
    GfxManager2D::ShaderID CreateShader(const char filepaths[GfxManager2D::ShaderStage::NUM_POSSIBLE]);
    /*************************************************************************/
    /*!
      \brief
        Creates a texture given the filename into an image.
      \param filepath
        The filepath to look for the texture starting from the current
        directory.
    */
    /*************************************************************************/
    GfxManager2D::TextureID CreateTexture(const char* filepath);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GfxFactory2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////
