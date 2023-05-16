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
 * \file            SimpleTextureManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture manager for simple renderer.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SimpleTextureManager_BARRAGE_H
#define SimpleTextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "SimpleTexture.hpp"

#include <unordered_map>
#include <string>

namespace Barrage
{
  typedef std::unordered_map<std::string, SimpleTexture*> SimpleTextureLibrary;

  //! Texture manager for simple renderer
  class SimpleTextureManager
  {
  public:
    SimpleTextureManager();

    ~SimpleTextureManager();

    const SimpleTexture* GetTexture(const std::string& name);

    void LoadTexture(const std::string& name);

    void UnloadTexture(const std::string& name);

  private:
    SimpleTextureLibrary library_;

    SimpleTexture* CreateTexture(const std::string& name);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SimpleTextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////