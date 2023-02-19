/* ========================================================================= */
/*!
 *
 * \file            GfxRegistry2D.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A helper module to register assets given a particular name.
 * Other helper systems use this module to query for assets.
 *
 */
 /* ========================================================================= */

// ============================================================================
// Includes
// ============================================================================
#include <stdafx.h>
#include "GfxRegistry2D.hpp"

#include <cassert>
#include <algorithm>

namespace Barrage
{
  GfxRegistry2D::GfxRegistry2D() : factory_(nullptr)
  {
  }

  void GfxRegistry2D::Initialize(GfxFactory2D& factory)
  {
    factory_ = &factory;
  }

  void GfxRegistry2D::Shutdown()
  {
    textureBook_.clear();
    shaderBook_.clear();
    factory_ = nullptr;
  }

  void GfxRegistry2D::RegisterTexture(const GfxManager2D::TextureID& texture, const char* keyname)
  {
    Register(texture, keyname, textureBook_);
  }

  void GfxRegistry2D::RegisterTexture(const char* path, const char* keyname)
  {
    assert(factory_);
    // If there is no explicit keyname then just the path as the keyname.
    if (!keyname)
    {
      keyname = path;
    }
    // Create the texture using the factory and register it.
    GfxManager2D::TextureID texture = factory_->CreateTexture(path);
    RegisterTexture(texture, keyname);
  }

  void GfxRegistry2D::RegisterShader(const GfxManager2D::ShaderID& shader, const char* keyname)
  {
    Register(shader, keyname, shaderBook_);
  }

  void GfxRegistry2D::RegisterShader(const char* const paths[ShaderStage::NUM_SHADERS_POSSIBLE], const char* keyname)
  {
    assert(factory_);
    // If there is no explicit keyname then just the path as the keyname.
    if (!keyname)
    {
      keyname = paths[0];
    }
    // Create the shader using the factory and register it to this system.
    GfxManager2D::ShaderID shader = factory_->CreateShader(paths);
    RegisterShader(shader, keyname);
  }

  GfxManager2D::TextureID GfxRegistry2D::FindTexture(const char* keyname)
  {
    return Find(keyname, textureBook_);
  }

  GfxManager2D::ShaderID GfxRegistry2D::FindShader(const char* keyname)
  {
    return Find(keyname, shaderBook_);
  }

  std::vector<std::string> GfxRegistry2D::GetTextureNames()
  {
    std::vector<std::string> textureNames;

    for (auto& entry : textureBook_)
    {
      textureNames.push_back(entry.first);
    }

    std::sort(textureNames.begin(), textureNames.end());
    
    return textureNames;
  }

  void GfxRegistry2D::Register(
    const GfxManager2D::ResourceID& resource, const char* keyname,
    ResourceBook& resourceBook)
  {
    resourceBook[keyname] = resource;
  }

  GfxManager2D::ResourceID GfxRegistry2D::Find(const char* keyname, ResourceBook& resourceBook)
  {
    // Attempt getting the resource with the key, if we don't find it then we return
    // an invalid resource.
    auto iter = resourceBook.find(keyname);
    if (iter != resourceBook.end())
    {
      return iter->second;
    }
    else
    {
      return GfxManager2D::TextureID();
    }
  }
}
