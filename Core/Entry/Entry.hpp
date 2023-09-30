/* ======================================================================== */
/*!
 * \file            Entry.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
     Contains the information needed to initialize a game.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Entry_BARRAGE_H
#define Entry_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

namespace Barrage
{
  //! Contains the information needed to initialize a game
  class Entry
  {
  public:
    class SpaceEntry
    {
    public:
      SpaceEntry();

      SpaceEntry(const std::string& name, const std::string& scene);

    public:
      std::string name_;
      std::string scene_;
    };

    void AddTexture(const std::string& textureName);

    void AddSpace(const SpaceEntry& space);

    static bool SaveToFile(const Entry& entry, const std::string& path);

    static Entry LoadFromFile(const std::string& path);

  public:
    std::vector<std::string> textures_;
    std::vector<SpaceEntry> spaces_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Entry_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////