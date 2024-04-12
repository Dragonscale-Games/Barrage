/* ======================================================================== */
/*!
 * \file            CreateSpawnArchetype.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new object archetype and adds it as a spawn archetype to a pool
   in the scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreateSpawnArchetype_BARRAGE_H
#define CreateSpawnArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Commands/Command.hpp"
#include "Objects/Archetypes/ObjectArchetype.hpp"

namespace Barrage
{
  //! Creates a spawn archetype and adds it to a pool in the scene
  class CreateSpawnArchetype : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the CreateSpawnArchetype command.

        \param sceneName
          The name of the scene to place the spawn archetype in.

        \param poolName
          The name of the pool to create the spawn archetype in.
      */
      /**************************************************************/
      CreateSpawnArchetype(const std::string& sceneName, const std::string& poolName);

    private:
      /**************************************************************/
      /*!
        \brief
          Creates the spawn archetype and adds it to a pool in the
          scene.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Removes the spawn archetype from the pool in the scene
          and removes it from the archetype manager.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Adds the previously removed spawn archetype back to the
          archetype manager and the pool in the scene.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string spawnArchetypeName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreateSpawnArchetype_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////