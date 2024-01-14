/* ======================================================================== */
/*!
 * \file            RenameSpawnArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a spawn archetype in a pool.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RenameSpawnArchetype_BARRAGE_H
#define RenameSpawnArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/ObjectArchetype.hpp>

namespace Barrage
{
  //! Renames a spawn archetype in a pool
  class RenameSpawnArchetype : public Command
  {
  public:
    /**************************************************************/
    /*!
      \brief
        Constructs the RenameStartingObject command.

      \param sceneName
        The name of the scene the object lives in.

      \param poolName
        The name of the pool the object lives in.

      \param spawnArchetypeName
        The current name of the spawn archetype to rename.

      \param newName
        The new name of the object.
    */
    /**************************************************************/
    RenameSpawnArchetype(
      const std::string& sceneName,
      const std::string& poolName,
      const std::string& spawnArchetypeName,
      const std::string& newName);

  private:
    /**************************************************************/
    /*!
      \brief
        Renames the spawn archetype.

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
    std::string newName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RenameSpawnArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////