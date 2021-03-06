/* ========================================================================= */
/*!
 *
 * \file            GfxFactory2D.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

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
    explicit GfxFactory2D();
    /*************************************************************************/
    /*!
      \brief
        Initializes the system given a particuluar graphics manager
        to create resources out of.
      \param manager
        A reference to the manager used to create resources.
    */
    /*************************************************************************/
    void Initialize(GfxManager2D& manager);
    /*************************************************************************/
    /*!
      \brief
        Shuts down the system by releasing the resources this holds.
    */
    /*************************************************************************/
    void Shutdown();

    /*************************************************************************/
    /*!
      \brief
        Creates a shader given the filenames of the shader starting
        from the current directory.
      \param filepaths
        The filepaths of each shader for the program created.
        The index into the array corresponds to the enumeration
        for the shader stages in GfxManager2D.
      \returns
        - A valid shader ID when successful.
        - An invalid shader ID if an error occurred.
    */
    /*************************************************************************/
    GfxManager2D::ShaderID CreateShader(const char* const filepaths[GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE]) const;
    /*************************************************************************/
    /*!
      \brief
        Creates a texture given the filename into an image.
      \param filepath
        The filepath to look for the texture starting from the current
        directory.
      \returns
        - A valid texture ID when successful.
        - An invalid texture ID if an error occurred.
    */
    /*************************************************************************/
    GfxManager2D::TextureID CreateTexture(const char* filepath);
  
  private:
    GfxManager2D* manager_; //!< The manager to make resources out of.
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GfxFactory2D_MODULE_H
////////////////////////////////////////////////////////////////////////////////
