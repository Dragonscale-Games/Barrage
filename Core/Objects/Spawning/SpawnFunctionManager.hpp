/* ======================================================================== */
/*!
 * \file            SpawnFunctionManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Keeps track of spawn functions and their names. A spawn function modifies
    how an object spawns. For instance, there may be a "MatchPosition" spawn 
    function that causes an object to be spawned at the same location as 
    its spawner.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnFunctionManager_BARRAGE_H
#define SpawnFunctionManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <unordered_map>
#include <string>

namespace Barrage
{
  class Pool;
  
  // Arguments: spawner pool, pool to spawn into, index of first new object, number of new objects, indices of spawner objects
  typedef void (*SpawnFunction)(Pool&, Pool&, unsigned, unsigned, const std::vector<unsigned>&);
  
  //! Associates spawn functions with their names
  typedef std::unordered_map<std::string_view, SpawnFunction> SpawnFunctionMap;

  //! Keeps track of spawn functions and their names
  class SpawnFunctionManager
	{
    public:   
      SpawnFunctionManager() = delete;
      
      /**************************************************************/
      /*!
        \brief
          Adds a spawn function to the manager's collection.

        \param name
          The name the user would like assigned to the spawn function.

        \param spawnFunction
          The spawn function to add.
      */
      /**************************************************************/
      static void RegisterSpawnFunction(const std::string_view& name, SpawnFunction spawnFunction);

      /**************************************************************/
      /*!
        \brief
          Gets a spawn function (if it was registered).

        \param name
          The name of a spawn function.

        \return
          Returns the spawn function with the given name, or nullptr 
          if it doesn't exist.
      */
      /**************************************************************/
      static SpawnFunction GetSpawnFunction(const std::string_view& name);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered initializers.

        \return
          Returns the list of all registered initializers.
      */
      /**************************************************************/
      static std::vector<std::string_view> GetSpawnFunctionNames();

    private:
      static SpawnFunctionMap spawnFunctions_;                  //!< The collection of registered spawn functions
      static std::vector<std::string_view> spawnFunctionNames_; //!< The names of all registered spawn functions
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnFunctionManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////