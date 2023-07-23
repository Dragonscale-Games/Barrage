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

#include "TextureManager.hpp"

#include <stb_image/stb_image.h>
#include <glad/gl.h>
#include <stdexcept>

namespace Barrage
{
  TextureManager::TextureManager() :
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

  void TextureManager::LoadTexture(const std::string& name)
  {
    std::string texture_path = "Assets/Textures/" + name + ".png";
    
    auto new_texture = std::make_shared<Texture>(texture_path);
    
    if (!new_texture->IsValid())
    {
      new_texture = defaultTexture_;
    }
    
    textures_[name] = new_texture;
  }

  void TextureManager::UnloadTexture(const std::string& name)
  {
    textures_.erase(name);
  }

  void TextureManager::Clear()
  {
    textures_.clear();
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

    defaultTexture_ = std::make_shared<Texture>(2, 2, imageData);
  }
}