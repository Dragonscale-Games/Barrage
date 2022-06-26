/* ========================================================================= */
/*!
 *
 * \file            ImageSource.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used for loading images from disk. 
 * In this specific case we make use of stb_image.
 */
/* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef ImageSource_MODULE_H
#define ImageSource_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <File/FileManager.hpp>
#include <Rendering/GfxManager2D.hpp>
#include <vector>

namespace Barrage
{
  //! Represents an image loaded as a resource.
  class ImageSource : public Resource
  {
  public:
    /*************************************************************************/
    /*************************************************************************/
    ImageSource(const std::string& path, const std::string& filename);
    /*************************************************************************/
    /*!
      \brief
        Releases all resources upon destruction.
    */
    /*************************************************************************/
    virtual ~ImageSource() = default;

  protected:
    /*************************************************************************/
    /*!
      \brief
        Loads the image specified by the filepath.
      \param filepath
        The file path to load the image from.
    */
    /*************************************************************************/
    virtual void Load(const std::string& filepath) noexcept(false) override;
    /*************************************************************************/
    /*!
      \brief
        Saves the image stored in this resource as a file on the disk
        under the specified filepath.
    */
    /*************************************************************************/
    virtual void Save(const std::string& filepath) const noexcept(false) override;

  private:
    //! The vector container storing the image as a byte buffer.
    std::vector<unsigned char> pixelBuffer_;
    //! The specifications of the file loaoded.
    GfxManager2D::TextureSpecs specs_;
  };
}

#endif // ImageSource_MODULE_H