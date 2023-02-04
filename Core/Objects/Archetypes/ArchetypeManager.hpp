/* ======================================================================== */
/*!
 * \file            ArchetypeManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Contains and manages all object and pool archetypes.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ArchetypeManager_BARRAGE_H
#define ArchetypeManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "PoolArchetype/PoolArchetype.hpp"
#include "ObjectArchetype/ObjectArchetype.hpp"
#include "Objects/Components/ComponentAllocator.hpp"

namespace Barrage
{
  //! Maps pool archetype names to pool archetypes
  typedef std::unordered_map<std::string_view, PoolArchetype*> PoolArchetypeMap;

  //! Maps object archetype names to object archetypes
  typedef std::unordered_map<std::string_view, ObjectArchetype*> ObjectArchetypeMap;

  //! <class description>
  class ArchetypeManager
	{
    public:   
      ArchetypeManager(ComponentAllocator& componentAllocator);

      ~ArchetypeManager();

      void AddPoolArchetype(const std::string_view& name, PoolArchetype* archetype);

      void AddObjectArchetype(const std::string_view& name, ObjectArchetype* archetype);

      PoolArchetype* GetPoolArchetype(const std::string_view& name);

      ObjectArchetype* GetObjectArchetype(const std::string_view& name);

      std::vector<std::string_view> GetPoolArchetypeNames();

      std::vector<std::string_view> GetObjectArchetypeNames();

      void LoadPoolArchetype(const std::string_view& name);

      void LoadObjectArchetype(const std::string_view& name);

      void SavePoolArchetype(const std::string_view& name);

      void SaveObjectArchetype(const std::string_view& name);

    private:
      PoolArchetypeMap poolArchetypes_;
      ObjectArchetypeMap objectArchetypes_;
      //ComponentAllocator& componentAllocator_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // ArchetypeManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////