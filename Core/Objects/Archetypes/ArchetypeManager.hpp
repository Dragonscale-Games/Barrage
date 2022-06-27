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

      void AddPoolArchetype(const std::string name, PoolArchetype* archetype);

      void AddObjectArchetype(const std::string name, ObjectArchetype* archetype);

      PoolArchetype* GetPoolArchetype(const std::string name);

      ObjectArchetype* GetObjectArchetype(const std::string name);

      std::vector<std::string> GetPoolArchetypeNames();

      std::vector<std::string> GetObjectArchetypeNames();

      void LoadPoolArchetype(const std::string name);

      void LoadObjectArchetype(const std::string name);

      void SavePoolArchetype(const std::string name);

      void SaveObjectArchetype(const std::string name);

    private:
      PoolArchetypeMap poolArchetypes_;
      ObjectArchetypeMap objectArchetypes_;
      //ComponentAllocator& componentAllocator_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // ArchetypeManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////