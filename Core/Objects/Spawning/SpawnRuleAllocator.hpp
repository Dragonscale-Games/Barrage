/* ======================================================================== */
/*!
 * \file            SpawnRuleAllocator.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of spawn rule via its name.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRuleAllocator_BARRAGE_H
#define SpawnRuleAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "SpawnRule.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

namespace Barrage
{
  typedef std::shared_ptr<SpawnRule> (*SpawnRuleAllocFunc)();
  typedef std::unordered_map<std::string, SpawnRuleAllocFunc> SpawnRuleAllocMap;

  //! Responsible for allocating new spawn rules
  class SpawnRuleAllocator
  {
    public:
      SpawnRuleAllocator() = delete;

      /**************************************************************/
      /*!
        \brief
          Tells the allocator how to allocate a spawn rule of a
          given type.

        \tparam T
          The type of spawn rule to register.

        \param name
          The name of the spawn rule.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterSpawnRule(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Creates a shared component whose type matches the given
          name. If no component with that name has been registered,
          returns nullptr.

        \return
          Returns a pointer to the newly allocated spawn rule if the
          component type has been registered, otherwise returns
          nullptr.
      */
      /**************************************************************/
      static std::shared_ptr<SpawnRule> CreateSpawnRule(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered spawn rules.

        \return
          Returns the list of all registered spawn rules.
      */
      /**************************************************************/
      static const std::vector<std::string>& GetSpawnRuleNames();

    private:
      /**************************************************************/
      /*!
        \brief
          Creates a spawn rule of the input type.

        \tparam T
          The type of spawn rule to allocate.

        \return
          Returns a shared pointer to the newly allocated spawn rule.
      */
      /**************************************************************/
      template <typename T>
      static std::shared_ptr<SpawnRule> AllocateSpawnRule();

    private:
      static SpawnRuleAllocMap spawnRuleAllocMap_;     //!< Maps names of spawn rules to their allocation functions
      static std::vector<std::string> spawnRuleNames_; //!< The names of all registered spawn rules
      static bool spawnRuleNamesSorted_;               //!< Flag for whether the spawn rule names are currently sorted
  };
}

#include "SpawnRuleAllocator.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRuleAllocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////