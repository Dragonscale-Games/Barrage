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
#include <Rendering/GfxTypes.hpp>
#include <vector>

namespace Barrage
{
  //! Represents an image loaded as a resource.
  class ImageSource : public FileResource
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Creates an image source given a path to the image file
        and it's file name.
      \param path
        The path to the image to where the image is saved.
      \param filename
        The name of the image.
    */
    /*************************************************************************/
    ImageSource(const std::string& path, const std::string& filename);
    /*************************************************************************/
    /*!
      \brief
        Releases all resources upon destruction.
    */
    /*************************************************************************/
    virtual ~ImageSource() = default;

    /*************************************************************************/
    /*!
      \brief
        Updates the image source using a new set of specs.
      \param specs
        The specs to update this image source with.
    */
    /*************************************************************************/
    void Update(const TextureSpecs& specs);
    /*************************************************************************/
    /*!
      \brief
        Gets the specifications of the currently loaded
        image source.
      \returns
        The texture specs for this image.
    */
    /*************************************************************************/
    const TextureSpecs& GetSpecs() const;

    void Save() const;

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
    TextureSpecs specs_;
  };
}

#endif // ImageSource_MODULE_H
