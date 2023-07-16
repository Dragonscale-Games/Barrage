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

namespace Barrage
{
  typedef std::unordered_map<std::string, Texture*> TextureLibrary;

  //! Texture manager for simple renderer
  class TextureManager
  {
  public:
    TextureManager();

    ~TextureManager();

    const Texture* GetTexture(const std::string& name);

    void LoadTexture(const std::string& name);

    void UnloadTexture(const std::string& name);

  private:
    TextureLibrary library_;

    Texture* CreateTexture(const std::string& name);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////