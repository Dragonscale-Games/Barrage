/* ======================================================================== */
/*!
 * \file            RenameStartingObject.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a starting object in a pool.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RenameStartingObject_BARRAGE_H
#define RenameStartingObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/ObjectArchetype.hpp>

namespace Barrage
{
  //! Renames a starting object in a pool
  class RenameStartingObject : public Command
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

        \param startingObjectName
          The current name of the object to rename.

        \param newName
          The new name of the object.
      */
      /**************************************************************/
      RenameStartingObject(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& startingObjectName,
        const std::string& newName);

    private:
      /**************************************************************/
      /*!
        \brief
          Renames the object.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Adds the object archetype back to its pool.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Removes the object archetype from its pool.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string startingObjectName_;
      std::string newName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RenameStartingObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////