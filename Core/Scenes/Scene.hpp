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

#include <Objects/Archetypes/PoolArchetype/PoolArchetype.hpp>

#include <unordered_map>
#include <string>

namespace Barrage
{
  //! A list of pools (and their objects) to spawn in a space
  class Scene
  {
    public:
      Scene(const std::string& name);

      Scene(const Scene& other);

      Scene& operator=(const Scene& other);

      ~Scene();

      const std::vector<PoolArchetype*>& GetPoolArchetypes();

      void AddPoolArchetype(PoolArchetype* archetype, unsigned* index = nullptr);

    private:
      void CopyPoolArchetypes(const std::vector<PoolArchetype*>& other);

      void DeletePoolArchetypes();

    private:
      std::string name_;
      std::vector<PoolArchetype*> poolArchetypes_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////