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

namespace Barrage
{
  GfxFactory2D::GfxFactory2D() : manager_(nullptr)
  {
  }

  void GfxFactory2D::Initialize(GfxManager2D& manager)
  {
    manager_ = &manager;
  }

  GfxManager2D::ShaderID GfxFactory2D::CreateShader(const char filepaths[GfxManager2D::ShaderStage::NUM_SHADERS_POSSIBLE])
  {
    UNREFERENCED(filepaths);
    assert(manager_);
    NO_IMPL();
    return GfxManager2D::ShaderID();
  }

  GfxManager2D::TextureID GfxFactory2D::CreateTexture(const char* filepath)
  {
    UNREFERENCED(filepath);
    assert(manager_);
    NO_IMPL();
    return GfxManager2D::TextureID();
  }
}
