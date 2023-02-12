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
  typedef std::unordered_map<std::string, PoolArchetype*> PoolArchetypeMap;

  //! Maps object archetype names to object archetypes
  typedef std::unordered_map<std::string, ObjectArchetype*> ObjectArchetypeMap;

  //! <class description>
  class ArchetypeManager
	{
    public:   
      ArchetypeManager(ComponentAllocator& componentAllocator);

      ~ArchetypeManager();

      void CreatePoolArchetype(const std::string& name);

      void CreateObjectArchetype(const std::string& name);

      void AddPoolArchetype(const std::string& name, PoolArchetype* archetype);

      void AddObjectArchetype(const std::string& name, ObjectArchetype* archetype);

      PoolArchetype* GetPoolArchetype(const std::string& name);

      ObjectArchetype* GetObjectArchetype(const std::string& name);

      void DeletePoolArchetype(const std::string& name);

      void DeleteObjectArchetype(const std::string& name);

      std::vector<std::string> GetPoolArchetypeNames();

      std::vector<std::string> GetObjectArchetypeNames();

    private:
      PoolArchetypeMap poolArchetypes_;
      ObjectArchetypeMap objectArchetypes_;
      //ComponentAllocator& componentAllocator_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // ArchetypeManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////