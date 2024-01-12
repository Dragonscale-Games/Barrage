/* ======================================================================== */
/*!
 * \file            Scene.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a list of pools (and their objects) to spawn in a space.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Scene_BARRAGE_H
#define Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Archetypes/PoolArchetype.hpp>

namespace Barrage
{
  //! A list of pools (and their objects) to spawn in a space
  class Scene
  {
    public:
      Scene();

      Scene(const std::string& name);

      void SetName(const std::string& name);

      const std::string& GetName();

      const PoolArchetypeMap& GetPoolArchetypes();

      bool SaveToFile(const Scene& scene, const std::string& path);

      Scene LoadFromFile(const std::string& path);

    public:
      std::string name_;
      PoolArchetypeMap poolArchetypes_;
  };

  using SceneMap = std::map<std::string, Scene>;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////