/* ======================================================================== */
/*!
 * \file            SpawnRuleFactory.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of spawn rule via its name.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnRuleFactory_BARRAGE_H
#define SpawnRuleFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "SpawnRule.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  using SpawnRuleFactoryMethod = DeepPtr<SpawnRule>(*)();
  using SpawnRuleFactoryMethodMap = std::map<std::string, SpawnRuleFactoryMethod>;

  //! Responsible for allocating new spawn rules
  class SpawnRuleFactory
  {
    public:
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
          Creates a spawn rule whose type matches the given
          name. If no spawn rule with that name has been registered,
          returns nullptr.

        \param name
          The name of the spawn rule to create.

        \return
          Returns a pointer to the newly allocated spawn rule if the
          spawn rule has been registered, otherwise returns nullptr.
      */
      /**************************************************************/
      static DeepPtr<SpawnRule> CreateSpawnRule(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered spawn rules.

        \return
          Returns the list of all registered spawn rules.
      */
      /**************************************************************/
      static const StringSet& GetSpawnRuleNames();

    private:
      SpawnRuleFactory() = delete;
      SpawnRuleFactory(const SpawnRuleFactory&) = delete;
      SpawnRuleFactory& operator=(const SpawnRuleFactory&) = delete;
      ~SpawnRuleFactory() = delete;
    
      /**************************************************************/
      /*!
        \brief
          Creates a spawn rule of the input type.

        \tparam T
          The type of spawn rule to allocate.

        \return
          Returns a pointer to the newly allocated spawn rule.
      */
      /**************************************************************/
      template <typename T>
      static DeepPtr<SpawnRule> AllocateSpawnRule();

    private:
      static SpawnRuleFactoryMethodMap spawnRuleFactoryMethodMap_; //!< Maps names of spawn rules to their allocation functions
      static StringSet spawnRuleNames_;                            //!< Names of all registered spawn rules
  };
}

#include "SpawnRuleFactory.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnRuleFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////