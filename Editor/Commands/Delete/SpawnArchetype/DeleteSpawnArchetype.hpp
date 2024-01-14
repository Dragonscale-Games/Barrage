/* ======================================================================== */
/*!
 * \file            DeleteSpawnArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes a spawn archetype from its pool.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeleteSpawnArchetype_BARRAGE_H
#define DeleteSpawnArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/ObjectArchetype.hpp>

namespace Barrage
{
  //! Removes a spawn archetype from its pool
  class DeleteSpawnArchetype : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the DeleteSpawnArchetype command.

        \param sceneName
          The name of the scene to remove the spawn archetype from.

        \param poolName
          The name of the pool to remove the spawn archetype from.

        \param spawnArchetypeName
          The name of the spawn archetype to remove.
      */
      /**************************************************************/
      DeleteSpawnArchetype(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& spawnArchetypeName);

    private:
      /**************************************************************/
      /*!
        \brief
          Removes the spawn archetype from its pool.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Adds the spawn archetype back to its pool.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Removes the spawn archetype from its pool.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string spawnArchetypeName_;

      ObjectArchetype undoArchetype_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteSpawnArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////