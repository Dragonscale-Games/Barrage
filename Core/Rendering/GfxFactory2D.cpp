/* ========================================================================= */
/*!
 *
 * \file            GfxFactory2D.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Makes creating any of the resources easier and data driven.
 * 
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include "stdafx.h"
#include "GfxFactory2D.hpp"

#include <sstream>
#include <fstream>
#include <stb_image/stb_image.h>

namespace Barrage
{
  GfxFactory2D::GfxFactory2D() : manager_(nullptr)
  {
  }

  void GfxFactory2D::Initialize(GfxManager2D& manager)
  {
    manager_ = &manager;
  }

  void GfxFactory2D::Shutdown()
  {
    manager_ = nullptr;
  }

  GfxManager2D::ShaderID GfxFactory2D::CreateShader(const char* const filepaths[GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE]) const
  {
    // Read the shader code from the files specified in the filepaths.
    // Store the strings read from the files in the array.
    std::array<std::stringstream, GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE> codes;
    // Create containers to store the codes.
    std::array<std::string, GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE> codeContainers;
    // The file handle to read shader code from.
    std::ifstream file;
    for(unsigned i = 0; i < GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE; ++i)
    {
      // Open the file and read from it.
      file.open(filepaths[i], std::ifstream::in);
      if(file.is_open())
      {
        // Add the version directive in addition to the code.
        // TODO: Find a way to do this programmatically so the directive isn't hardcoded.
        codes[i] << "#version 330 core" << std::endl;
        codes[i] << file.rdbuf();
      }
      // Close the file handle before doing anything destructive.
      file.close();
      // Check if the file went bad and if so, we exit early with an invalid shader.
      if(!file.good())
      {
        return GfxManager2D::ShaderID();
      }
    }
    // Start filling out the form to create the shader.
    GfxManager2D::ShaderSpecs specs = {};
    // After reading all the files without getting any errors, we start attempting to compile
    // the shader.
    for(unsigned i = 0; i < GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE; ++i)
    {
      codeContainers[i] = codes[i].str();
    }
    for(unsigned i = 0; i < GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE; ++i)
    {
      specs.stageSources_[i] = codeContainers[i].c_str();
    }
    // Create the shader.
    assert(manager_);
    return manager_->CreateShader(specs);
  }

  GfxManager2D::TextureID GfxFactory2D::CreateTexture(const char* filepath)
  {
    // Reads 2D images but not necessarily 3D ones.
    // TODO: Figure out a solution to read a cubemap if necessary.
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(filepath, &width, &height, &channels, 4);

    GfxManager2D::TextureSpecs textureSpecs = { 0 };
    textureSpecs.createMipmaps_ = true;
    textureSpecs.dimensions_ = 2;
    textureSpecs.format_ = TextureFormat::R8G8B8A8;
    textureSpecs.width_ = width;
    textureSpecs.height_ = height;
    textureSpecs.pixels_ = reinterpret_cast<const unsigned char* const>(pixels);

    assert(manager_);
    GfxManager2D::TextureID newTexture = manager_->CreateTexture(textureSpecs);
    stbi_image_free(pixels);

    return newTexture;
  }
}
