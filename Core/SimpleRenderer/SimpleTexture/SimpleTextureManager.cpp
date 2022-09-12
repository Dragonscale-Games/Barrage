/*
MIT License

Copyright(c) 2022 Dragonscale-Games

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ======================================================================== */
/*!
 * \file            SimpleTextureManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture manager for simple renderer.
 */
 /* ======================================================================== */

#include "SimpleTextureManager.hpp"

#include <stb_image/stb_image.h>
#include <glad/gl.h>
#include <stdexcept>

namespace Barrage
{
  SimpleTextureManager::SimpleTextureManager() :
    library_()
  {
    stbi_set_flip_vertically_on_load(true);
  }

  SimpleTextureManager::~SimpleTextureManager()
  {
    for (const auto& i : library_)
    {
      delete i.second;
    }
  }

  const SimpleTexture* SimpleTextureManager::GetTexture(const std::string& name)
  {
    auto texture = library_.find(name);

    if (texture == library_.end())
    {
      return CreateTexture(name);
    }

    return texture->second;
  }

  void SimpleTextureManager::LoadTexture(const std::string& name)
  {
    auto texture = library_.find(name);

    if (texture == library_.end())
    {
      CreateTexture(name);
    }
  }

  void SimpleTextureManager::UnloadTexture(const std::string& name)
  {
    if (name == "All")
    {
      for (auto texture : library_)
      {
        delete texture.second;
      }

      library_.clear();
    }
    else
    {
      auto texture = library_.find(name);

      if (texture != library_.end())
      {
        delete texture->second;
        library_.erase(texture);
      }
    }
  }

  SimpleTexture* SimpleTextureManager::CreateTexture(const std::string& name)
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

    SimpleTexture* new_texture = new SimpleTexture(texture_id);

    library_[name] = new_texture;

    return new_texture;
  }
}