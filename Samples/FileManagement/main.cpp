/* ======================================================================== */
/*!
 * \file            main.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
   A sample file showing the features available for file management in
   Barrage.
 */
/* ======================================================================== */

/* ======================================================================== */
/* Includes */
/* ======================================================================== */

#include <stdafx.h>
#include <iostream>
#include <File/FileManager.hpp>

/****************************************************************************/
/*!
  \brief
    Runs a demo for getting standard directories in Barrage.
  \param manager
    The file manager used for the demo.
*/
/****************************************************************************/
void DirectoryDemo(Barrage::FileManager& manager);
void SaveResourceDemo(Barrage::FileManager& manager);

/****************************************************************************/
/*!
  \brief
    The entry point for testing debug features.
*/
/****************************************************************************/
int main()
{
  using Barrage::FileManager;
  FileManager fileManager;
  fileManager.Initialize();
  // Run the demos!
  DirectoryDemo(fileManager);
  SaveResourceDemo(fileManager);
  // Shut down the system and quit.
  fileManager.Shutdown();
  return 0;
}

void DirectoryDemo(Barrage::FileManager& manager)
{
  using Barrage::FileManager;
  std::cout << "User Path: " << manager.GetUserPath() << std::endl;
  std::cout << "Content Path: " << manager.GetContentPath() << std::endl;
}

#include <File/Graphics/ImageSource.hpp>
void SaveResourceDemo(Barrage::FileManager& manager)
{
  using Barrage::ImageSource;
  using Barrage::TextureSpecs;
  using Barrage::TextureFilter;
  using Barrage::TextureFormat;
  using Barrage::FileManager;

  // Creates a file manager.
  FileManager fileManager;
  fileManager.Initialize();
  // The constant data about this texture.
  const uint8_t width = 3;
  const uint8_t height = 3;
  const uint8_t dimensions = 2;
  // The pixel data for the texture.
  unsigned int pixels[width * height] = {
    0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
    0x00000000, 0xFFFFFFFF, 0x00000000,
    0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
  };
  // The specifications for the sample texture.
  TextureSpecs specs{};
  specs.width_ = width;
  specs.height_ = height;
  specs.dimensions_ = dimensions;
  specs.createMipmaps_ = true;
  specs.format_ = TextureFormat::R8G8B8A8;
  specs.filter_ = TextureFilter::FILTER_NONE;
  specs.pixels_ = reinterpret_cast<unsigned char*>(pixels);
  // Creates an image source, updates it with texture data, and saving it.
  ImageSource image(manager.GetUserPath(), "image.png");
  //ImageSource image(manager.GetContentPath(), "image.png");
  //ImageSource image("./", "image.png");
  image.Update(specs);
  image.Save();

  UNREFERENCED(image);
}
