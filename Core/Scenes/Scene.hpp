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
#include "Serialization/Serializer.hpp"

namespace Barrage
{
  //! A list of pools (and their objects) to spawn in a space
  class Scene
  {
    public:
      Scene(const std::string& name);

      Scene(const rapidjson::Value& data);

      Scene(const Scene& other);

      Scene& operator=(const Scene& other);

      ~Scene();

      bool HasPool(const std::string& name);

      void SetName(const std::string& name);

      const std::string& GetName();

      PoolArchetype* GetPoolArchetype(const std::string& name);

      const std::vector<PoolArchetype*>& GetPoolArchetypes();

      void AddPoolArchetype(PoolArchetype* archetype, unsigned* index = nullptr);

      PoolArchetype* ExtractPoolArchetype(const std::string& name, unsigned* index = nullptr);

      rapidjson::Value Serialize(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

      static bool SaveToFile(Scene* scene, const std::string& path);

      static Scene* LoadFromFile(const std::string& path);

    private:
      void CopyPoolArchetypes(const std::vector<PoolArchetype*>& other);

      void DeletePoolArchetypes();

      rapidjson::Value SerializePoolArchetypes(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator);

      void DeserializePoolArchetypes(const rapidjson::Value& data);

    private:
      std::string name_;
      std::vector<PoolArchetype*> poolArchetypes_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Scene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////