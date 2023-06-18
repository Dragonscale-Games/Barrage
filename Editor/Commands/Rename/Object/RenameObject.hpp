/* ======================================================================== */
/*!
 * \file            RenameObject.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames an object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RenameObject_BARRAGE_H
#define RenameObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp>

namespace Barrage
{
  //! Renames an object
  class RenameObject : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the RenameObject command.

        \param sceneName
          The name of the scene the object lives in.

        \param poolName
          The name of the pool the object lives in.

        \param objectName
          The current name of the object to rename.

        \param newName
          The new name of the object.
      */
      /**************************************************************/
      RenameObject(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& objectName,
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
          Adds the object archetype back to the scene and the
          archetype manager.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Removes the object archetype from the scene and the
          archetype manager.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string objectName_;
      std::string newName_;
  };
}


////////////////////////////////////////////////////////////////////////////////
#endif // RenameObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////