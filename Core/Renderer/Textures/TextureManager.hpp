/* ======================================================================== */
/*!
 * \file            TextureManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture manager for renderer.
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
#include <memory>

namespace Barrage
{
  typedef std::unordered_map<std::string, std::shared_ptr<Texture>> TextureMap;

  //! Texture manager for renderer
  class TextureManager
  {
    public:
      TextureManager();

      void Initialize();

      void Shutdown();

      void BindTexture(const std::string& name);

      void LoadTexture(const std::string& name);

      void UnloadTexture(const std::string& name);

      void Clear();

      std::vector<std::string> GetTextureNames();

    private:
      std::shared_ptr<Texture> defaultTexture_;
      TextureMap textures_;

      void CreateDefaultTexture();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////