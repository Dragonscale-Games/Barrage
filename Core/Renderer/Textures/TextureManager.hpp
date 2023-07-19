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

////////////////////////////////////////////////////////////////////////////////
#ifndef TextureManager_BARRAGE_H
#define TextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Texture.hpp"

#include <unordered_map>
#include <string>
#include <vector>

namespace Barrage
{
  typedef std::unordered_map<std::string, Texture*> TextureMap;

  //! Texture manager for simple renderer
  class TextureManager
  {
  public:
    TextureManager();

    ~TextureManager();

    const Texture* GetTexture(const std::string& name);

    void LoadTexture(const std::string& name);

    void UnloadTexture(const std::string& name);

    void UnloadTextures();

    std::vector<std::string> GetTextureNames();

  private:
    TextureMap textures_;

    Texture* CreateTexture(const std::string& name);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////