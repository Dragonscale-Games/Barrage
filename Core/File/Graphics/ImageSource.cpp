/* ========================================================================= */
/*!
 *
 * \file            ImageSource.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used for loading images from disk. 
 * In this specific case we make use of stb_image.
 */
/* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include <stdafx.h>
#include "ImageSource.hpp"

#include <stdexcept>
#include <algorithm>
#include <stb_image/stb_image.h>

namespace Barrage
{
  ImageSource::ImageSource(const std::string& path, const std::string& filename) :
    Resource(path, filename), pixelBuffer_(), specs_{}
  {
  }

  void ImageSource::Load(const std::string& filepath) noexcept(false)
  {
    // Load the image from file.
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(filepath.c_str(), &width, &height, &channels, 4);
    if(pixels)
    {
      // Transfer the pixel data over our buffer.
      const size_t textureSize = width * height * channels * sizeof(unsigned char);
      pixelBuffer_.resize(textureSize);
      std::copy(pixels, pixels + textureSize, pixelBuffer_.data());
      stbi_image_free(pixels);
      // Save the specs of the image we just loaded.
      specs_.createMipmaps_ = true;
      specs_.dimensions_ = 2;
      specs_.format_ = TextureFormat::R8G8B8A8;
      specs_.width_ = width;
      specs_.height_ = height;
      specs_.pixels_ = pixelBuffer_.data();
    }
    else
    {
      throw std::runtime_error("Failed to load the image at filepath: " + filepath);
    }
  }

  void ImageSource::Save(const std::string& filepath) const noexcept(false)
  {
    UNREFERENCED(filepath);
    NO_IMPL();
    throw std::runtime_error("Failed to save the image at filepath: " + filepath);
  }
}
