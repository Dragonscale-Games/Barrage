/* ======================================================================== */
/*!
 * \file            SpawnFuncManager.hpp
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
#ifndef SpawnFuncManager_BARRAGE_H
#define SpawnFuncManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <unordered_map>

namespace Barrage
{
  class Pool;
  
  // Arguments: spawner pool, pool to spawn into, index of first new object, number of new objects, indices of spawner objects
  typedef void (*SpawnFunc)(Pool&, Pool&, unsigned, unsigned, const std::vector<unsigned>&);
  
  //! Associates spawn functions with their names
  typedef std::unordered_map<std::string, SpawnFunc> SpawnFuncMap;

  //! Keeps track of spawn functions and their names
  class SpawnFuncManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      SpawnFuncManager();

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
      void RegisterSpawnFunc(const std::string name, SpawnFunc spawnFunction);

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
      SpawnFunc GetSpawnFunc(const std::string name);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered initializers.

        \return
          Returns the list of all registered initializers.
      */
      /**************************************************************/
      std::vector<std::string> GetSpawnFuncNames();

    private:
      SpawnFuncMap spawnFuncs_;                 //!< The collection of registered spawn functions
      std::vector<std::string> spawnFuncNames_; //!< The names of all registered spawn functions
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnFuncManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////