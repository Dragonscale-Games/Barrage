/* ======================================================================== */
/*!
 * \file            TestTextureManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary texture manager to make it convenient to test game systems.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TestTextureManager_BARRAGE_H
#define TestTextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "TestTexture.hpp"

#include <unordered_map>
#include <string>

namespace Barrage
{
  class TestTexture;

  typedef std::unordered_map<std::string, TestTexture*> TestTextureLibrary;

  //! Temporary texture manager to make it convenient to test game systems.
  class TestTextureManager
  {
  public:
    static TestTextureManager& Instance();

    ~TestTextureManager();

    TestTextureManager(TestTextureManager& other) = delete;

    void operator=(const TestTextureManager& rhs) = delete;

    const TestTexture* GetTexture(const std::string& name);

    void LoadTexture(const std::string& name);

    void UnloadTexture(const std::string& name);

  private:
    TestTextureLibrary library_;

    TestTextureManager();

    TestTexture* CreateTexture(const std::string& name);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TestTextureManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////