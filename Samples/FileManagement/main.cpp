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
#include <vector>
#include <string>
#include <File/FileManager.hpp>
#include <Serialization/ComponentRefl.cpp>

struct SerializationTest
{
  std::vector<std::string> sVector;
  std::vector<int> iVector;
  std::vector<float> fVector;
  std::vector<double> dVector;

  Barrage::CircleCollider circle;
  Barrage::BoundaryBox boundary;
  std::string s;
  
  int i;
  unsigned u;
  float f;
  double d;

  // Create a constructor for this test object to avoid a
  // compiler warning.
  SerializationTest() :
    i(), u(), f(), d()
  {};
};

struct GameFrameTest
{
  size_t frameID_;
  Barrage::CircleCollider circle_;
};

struct SimulationTest
{
  std::vector<GameFrameTest> frames_;
};

RTTR_REGISTRATION
{

// Reflect all the core Barrage objects.
Barrage::ReflectBarrageCore();

// A temporary test of what a frame might look like.
rttr::registration::class_<GameFrameTest>("GameFrameTest")
.property("frameID", &GameFrameTest::frameID_)
.property("circle", &GameFrameTest::circle_);

// A structure that simulates frames of simulation.
rttr::registration::class_<SimulationTest>("SimulationTest")
.property("frames", &SimulationTest::frames_);

// Temporary Colliders Class.
rttr::registration::class_<SerializationTest>("SerializationTest")
.property("sVector", &SerializationTest::sVector)
.property("iVector", &SerializationTest::iVector)
.property("fVector", &SerializationTest::fVector)
.property("dVector", &SerializationTest::dVector)

.property("s", &SerializationTest::s)
.property("circle", &SerializationTest::circle)
.property("boundary", &SerializationTest::boundary)

.property("i", &SerializationTest::i)
.property("u", &SerializationTest::u)
.property("f", &SerializationTest::f)
.property("d", &SerializationTest::d);
}

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
  fileManager.Initialize("Documents/Barrage/UserContent/");
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
  manager.Save(image);
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
  
  // Create our write and read test colliders.
  SerializationTest colliders;
  SerializationTest readColliders;

  SimulationTest readSimulation;

  {
    using Barrage::CircleCollider;
    CircleCollider circle;
    circle.radius_ = 25.0f;

    using Barrage::BoundaryBox;
    BoundaryBox box;
    box.xMin_ = 0.0f;
    box.yMin_ = 0.0f;
    box.xMax_ = 50.0f;
    box.yMax_ = 30.0f;

    colliders.sVector = { "one", "two", "three", "four", "five" };
    colliders.iVector = { 1, 2, 3, 4, 5 };
    colliders.fVector = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };
    colliders.dVector = { 0.01, 0.02, 0.03, 0.04, 0.05 };

    colliders.i = 1;
    colliders.u = 2u;
    colliders.f = 3.0f;
    colliders.d = 4.0;
    colliders.s = "Hello World!";
    colliders.boundary = box;
    colliders.circle = circle;

    SimulationTest simulation = {};
    size_t simulationLength = 5u;

    simulation.frames_.reserve(simulationLength);
    for (size_t frame = 0; frame < simulationLength; ++frame)
    {
      GameFrameTest frameData = {};
      frameData.frameID_ = frame;
      // Do a fake simulation of this circle collider expanding.
      const float dt = 1.0f / 16.0f;
      const float velocity = 2.0f;
      circle.radius_ += dt * velocity;
      frameData.circle_ = circle;
      // Add the frame to the simulation.
      simulation.frames_.push_back(frameData);
    }

    // Create an ObjectSource file and create a bogus object.
    ObjectSource& objectSource = manager.Create<ObjectSource>(manager.GetUserPath(), "SampleCollider.json");
    rapidjson::Document& doc = objectSource.GetDocument();
    doc.SetObject();

    // Serialize a core test.
    rapidjson::Value coreTest = Barrage::Serialize(colliders, doc.GetAllocator());
    doc.AddMember("SerializationTest", coreTest, doc.GetAllocator());
    // Serialize a simulation.
    rapidjson::Value simulationTest = Barrage::Serialize(simulation, doc.GetAllocator());
    doc.AddMember("Simulation", simulationTest, doc.GetAllocator());

    ((Barrage::FileResource&)objectSource).Save();
  }
  
  {
    const ObjectSource& objectSource = manager.Load<ObjectSource>(manager.GetUserPath(), "SampleCollider.json");
    const rapidjson::Document& doc = objectSource.GetDocument();
    const rapidjson::Value& root = doc.GetObject();
    Barrage::Deserialize(readColliders, root["SerializationTest"]);
    Barrage::Deserialize(readSimulation, root["Simulation"]);
  }
}
