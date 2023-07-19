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
    textures_()
  {
    stbi_set_flip_vertically_on_load(true);
  }

  TextureManager::~TextureManager()
  {
    for (const auto& i : textures_)
    {
      delete i.second;
    }
  }

  const Texture* TextureManager::GetTexture(const std::string& name)
  {
    auto texture = textures_.find(name);

    if (texture == textures_.end())
    {
      return CreateTexture(name);
    }

    return texture->second;
  }

  void TextureManager::LoadTexture(const std::string& name)
  {
    auto texture = textures_.find(name);

    if (texture == textures_.end())
    {
      CreateTexture(name);
    }
  }

  void TextureManager::UnloadTexture(const std::string& name)
  {
    auto texture = textures_.find(name);

    if (texture != textures_.end())
    {
      delete texture->second;
      textures_.erase(texture);
    }
  }

  void TextureManager::UnloadTextures()
  {
    for (auto texture : textures_)
    {
      delete texture.second;
    }

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

  Texture* TextureManager::CreateTexture(const std::string& name)
  {
    int width, height, channels;

    std::string texture_path = "Assets/Textures/" + name + ".png";

    unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
      throw std::runtime_error("Could not load texture.");
    }

    unsigned texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    Texture* new_texture = new Texture(texture_id);

    textures_[name] = new_texture;

    return new_texture;
  }
}