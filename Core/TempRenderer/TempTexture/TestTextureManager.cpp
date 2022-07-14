/* ======================================================================== */
/*!
 * \file            TestTextureManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary texture manager to make it convenient to test game systems.
 */
 /* ======================================================================== */

#include "stdafx.h"

#include "TestTextureManager.hpp"

#include <stb_image/stb_image.h>
//#include <glad/gl.h>
#include <glad/glad.h>
#include <stdexcept>

namespace Barrage
{
  TestTextureManager& TestTextureManager::Instance()
  {
    static TestTextureManager instance;
    return instance;
  }

  TestTextureManager::TestTextureManager() :
    library_()
  {
    stbi_set_flip_vertically_on_load(true);
  }

  TestTextureManager::~TestTextureManager()
  {
    for (const auto& i : library_)
    {
      delete i.second;
    }
  }

  const TestTexture* TestTextureManager::GetTexture(const std::string& name)
  {
    auto texture = library_.find(name);

    if (texture == library_.end())
    {
      return CreateTexture(name);
    }

    return texture->second;
  }

  void TestTextureManager::LoadTexture(const std::string& name)
  {
    auto texture = library_.find(name);

    if (texture == library_.end())
    {
      CreateTexture(name);
    }
  }

  void TestTextureManager::UnloadTexture(const std::string& name)
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

  TestTexture* TestTextureManager::CreateTexture(const std::string& name)
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

    TestTexture* new_texture = new TestTexture(texture_id);

    library_[name] = new_texture;

    return new_texture;
  }
}