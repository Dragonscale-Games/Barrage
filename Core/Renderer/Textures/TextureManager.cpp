/* ======================================================================== */
/*!
 * \file            TextureManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture manager for simple renderer.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "TextureManager.hpp"

#include <stb_image/stb_image.h>
#include <glad/gl.h>

#include <stdexcept>

namespace Barrage
{
  TextureManager::TextureManager() :
    textureDirectory_("Assets/Textures/"),
    defaultTexture_(),
    textures_()
  {
    stbi_set_flip_vertically_on_load(true);
  }

  void TextureManager::Initialize()
  {
    CreateDefaultTexture();
  }

  void TextureManager::Shutdown()
  {
    Clear();
  }

  void TextureManager::BindTexture(const std::string& name)
  { 
    if (textures_.count(name) == 0)
    {
      LoadTexture(name);
    }

    textures_.at(name)->Bind();
  }

  bool TextureManager::LoadTexture(const std::string& name)
  { 
    std::string texture_path = textureDirectory_ + name + ".png";
    
    auto new_texture = std::make_shared<Texture>(texture_path);
    
    bool success = new_texture->IsValid();

    if (!success)
    {
      new_texture = defaultTexture_;
    }
    
    textures_[name] = new_texture;

    return success;
  }

  void TextureManager::UnloadTexture(const std::string& name)
  {
    textures_.erase(name);
  }

  void TextureManager::Clear()
  {
    textures_.clear();
  }

  void TextureManager::SetTextureDirectory(const std::string& textureDirectory)
  {
    textureDirectory_ = textureDirectory;

    if (textureDirectory_.back() != '\\' && textureDirectory_.back() != '/')
    {
      textureDirectory_.push_back('/');
    }
  }

  std::vector<std::string> TextureManager::GetTextureNames()
  {
    std::vector<std::string> result;
    
    for (auto it = textures_.begin(); it != textures_.end(); ++it)
    {
      result.push_back(it->first);
    }

    return result;
  }

  void TextureManager::CreateDefaultTexture()
  {
    const GLubyte imageData[] = {
      128,   0, 128, 255, // Purple (Top-left)
        0, 128,   0, 255, // Green (Top-right)
        0, 128,   0, 255, // Green (Bottom-left)
      128,   0, 128, 255  // Purple (Bottom-right)
    };

    defaultTexture_ = std::make_shared<Texture>(2, 2, 4, imageData, GL_NEAREST);
  }
}