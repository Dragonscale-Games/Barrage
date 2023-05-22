/* ======================================================================== */
/*!
 * \file            main.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
   A sample file on how to use the rendering engine provided by Barrage.
 */
/* ======================================================================== */

/* ======================================================================== */
/* Includes */
/* ======================================================================== */

/*
#include <Debug/MemoryDebugger.hpp>
#include <Debug/MemoryOverrides.hpp>
*/

#include <Rendering/GfxPrimitives.hpp>
#include <Rendering/GfxManager2D.hpp>
#include <Rendering/GfxRenderer2D.hpp>
#include <Rendering/GfxFactory2D.hpp>
#include <Rendering/GfxRegistry2D.hpp>
#include <Rendering/GfxDraw2D.hpp>

#include <Rendering/WindowManager.hpp>

Barrage::GfxManager2D::TextureID CreateSampleTexture(Barrage::GfxManager2D& manager);

/****************************************************************************/
/*!
  \brief
    The entry point for testing graphics code.
*/
/****************************************************************************/
int main()
{
  using namespace Barrage;

  // The windowing module.
  Barrage::WindowManager windowing;
  Barrage::WindowManager::WindowData initSettings = {};
  initSettings.decorated_ = true;
  initSettings.width_ = 1920;
  initSettings.height_ = 1080;
  initSettings.title_ = "Barrage - Graphics Sample";
  windowing.Initialize(initSettings);
  windowing.ResizeToWindowed();
  initSettings = windowing.GetSettings();

  // The resources manager for the graphics system.
  Barrage::GfxManager2D manager;
  manager.Initialize(windowing);
  // The rendering module.
  Barrage::GfxRenderer2D renderer;
  renderer.Initialize(manager);
  renderer.SetBackgroundColor(glm::vec4(0.2f, 0.1f, 0.1f, 1.0f));
  // The factory module that lets the user create
  // resources for the graphics modules from files.
  Barrage::GfxFactory2D factory;
  factory.Initialize(manager);
  // The registry module so users can store resources created
  // from disk.
  Barrage::GfxRegistry2D registry;
  registry.Initialize(factory);
  // Register a sample shader from a file.
  const std::array<const char*, ShaderStage::NUM_SHADERS_POSSIBLE> filepaths = {
    "Assets/instanced.vs", "Assets/instanced.fs"
  };
  registry.RegisterShader(filepaths.data(), "instanced");
  // Register the texture wanted from a file.
  const Barrage::GfxManager2D::TextureID sampleTexture = CreateSampleTexture(manager);
  registry.RegisterTexture(sampleTexture, "sample");
  // The drawing module that simplifies rendering.
  Barrage::GfxDraw2D drawing;
  drawing.Initialize(manager, renderer, registry);
  drawing.ApplyShader("instanced");
  
  // Update the window while it's open.
  while(windowing.IsOpen())
  {
    windowing.PollEvents();
    // Note that you don't have to resubmit requests if
    // don't need to.
    const WindowManager::WindowData& settings = windowing.GetSettings();
    const glm::vec2 dimensions(settings.width_, settings.height_);
    renderer.SetViewportSpace(dimensions);
    // Tell the drawing system to draw a couple of squares on the screen.
    constexpr int size = 2;
    glm::vec2 positions[size] = { glm::vec2(-100 + settings.width_ / 2, settings.height_ / 2), glm::vec2(100 + settings.width_ / 2, settings.height_ / 2) };
    glm::vec2 scales[size] = { glm::vec2(150.0f), glm::vec2(50.0f, 120.0f) };
    glm::vec4 uvs[size] = { glm::vec4(glm::vec2(0), glm::vec2(1)), glm::vec4(glm::vec2(0), glm::vec2(1)) };
    RADIAN rotations[size] = { 0.25f * (22.0f / 7.0f), 0.0f };
    drawing.StartFrame();
    drawing.DrawInstancedQuad(size, positions, scales, rotations, uvs, "sample");
    drawing.EndFrame();
  }
  
  drawing.Shutdown();
  registry.Shutdown();
  renderer.Shutdown();
  manager.Shutdown();
  windowing.Shutdown();

  return 0;
}

Barrage::GfxManager2D::ShaderID CreateSampleTexture(Barrage::GfxManager2D& manager)
{
  using namespace Barrage;
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
  // Create the texture.
  return manager.CreateTexture(specs);
}
