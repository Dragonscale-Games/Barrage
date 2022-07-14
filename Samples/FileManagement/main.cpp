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
#include <Serialization/ComponentRefl.cpp>

/****************************************************************************/
/*!
  \brief
    Runs a demo for getting standard directories in Barrage.
  \param manager
    The file manager used for the demo.
*/
/****************************************************************************/
void DirectoryDemo(Barrage::FileManager& manager);
void SaveImageDemo(Barrage::FileManager& manager);
void LoadImageDemo(Barrage::FileManager& manager);
void SaveJSONDemo(Barrage::FileManager& manager);
void SerializationDemo(Barrage::FileManager& manager);

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
  SaveJSONDemo(fileManager);
  SerializationDemo(fileManager);
  SaveImageDemo(fileManager);
  LoadImageDemo(fileManager);
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
void SaveImageDemo(Barrage::FileManager& manager)
{
  using Barrage::ImageSource;
  using Barrage::TextureSpecs;
  using Barrage::TextureFilter;
  using Barrage::TextureFormat;
  using Barrage::FileManager;

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
  //ImageSource image(manager.GetUserPath(), "image.png");
  ImageSource& image = manager.Create<ImageSource>(manager.GetUserPath(), "image.png");
  image.Update(specs);
  image.Save();
}

void LoadImageDemo(Barrage::FileManager& manager)
{
  using Barrage::ImageSource;

  const ImageSource& image = manager.Load<ImageSource>(manager.GetUserPath(), "image.png");
  (void)image;
}

#include <File/Objects/ObjectSource.hpp>
void SaveJSONDemo(Barrage::FileManager& manager)
{
  using Barrage::ObjectSource;
  // Create an ObjectSource file and create a bogus object.
  ObjectSource& objectSource = manager.Create<ObjectSource>(manager.GetUserPath(), "Sample.json");
  rapidjson::Document& doc = objectSource.GetDocument();
  doc.SetObject();

  rapidjson::Value root(rapidjson::kObjectType);

  root.AddMember("Boolean", false, doc.GetAllocator());
  doc.AddMember("Root", root, doc.GetAllocator());

  ((Barrage::FileResource&)objectSource).Save();
}

#include <Serialization/Serializer.hpp>
#include <Objects/Components/SharedComponents/CircleCollider.hpp>
#include <Objects/Components/SharedComponents/BoundaryBox.hpp>
void SerializationDemo(Barrage::FileManager& manager)
{
  using Barrage::ObjectSource;
  // Create a sample circle collider to test.
  
  using Barrage::CircleCollider;
  CircleCollider circle;
  circle.radius_ = 50.0f;

  using Barrage::BoundaryBox;
  BoundaryBox box;
  box.xMin_ = 0.0f;
  box.yMin_ = 0.0f;
  box.xMax_ = 50.0f;
  box.yMax_ = 30.0f;

  Colliders colliders;
  colliders.boundary_ = box;
  colliders.circle_ = circle;

  // Create an ObjectSource file and create a bogus object.
  ObjectSource& objectSource = manager.Create<ObjectSource>(manager.GetUserPath(), "SampleCollider.json");
  rapidjson::Document& doc = objectSource.GetDocument();
  doc.SetObject();

  rapidjson::Value root = Barrage::Serialize(colliders, doc.GetAllocator());
  doc.AddMember("Collider", root, doc.GetAllocator());

  ((Barrage::FileResource&)objectSource).Save();
}
