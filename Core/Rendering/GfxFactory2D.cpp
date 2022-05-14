/* ========================================================================= */
/*!
 *
 * \file            GfxFactory2D.cpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

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

namespace Barrage
{
  GfxFactory2D::GfxFactory2D() : manager_(nullptr)
  {
  }

  void GfxFactory2D::Initialize(GfxManager2D& manager)
  {
    manager_ = &manager;
  }

  GfxManager2D::ShaderID GfxFactory2D::CreateShader(const char* filepaths[GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE])
  {
    // Read the shader code from the files specified in the filepaths.
    // Store the strings read from the files in the array.
    std::array<std::stringstream, GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE> codes;
    // The file handle to read shader code from.
    std::ifstream file;
    for(unsigned i = 0; i < GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE; ++i)
    {
      // Open the file and read from it.
      file.open(filepaths[i], std::ifstream::in);
      if(file.is_open())
      {
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
      specs.stageSources_[i] = codes[i].str().c_str();
    }
    // Create the shader.
    assert(manager_);
    return manager_->CreateShader(specs);
  }

  GfxManager2D::TextureID GfxFactory2D::CreateTexture(const char* filepath)
  {
    UNREFERENCED(filepath);
    assert(manager_);
    NO_IMPL();
    return GfxManager2D::TextureID();
  }
}
