/* ======================================================================== */
/*!
 * \file            EditComponentArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Edits the value of a component array in a starting object.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef EditComponentArray_BARRAGE_H
#define EditComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <rttr/variant.h>

namespace Barrage
{
  //! Edits the value of a component array in an object archetype
  class EditComponentArray : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param sceneName
          The scene containing the relevant pool.

        \param poolName
          The pool archetype containing the relevant object.

        \param objectName
          The object with the component array to edit.

        \param componentArrayName
          The name of the component array to edit.

        \param isSpawnArchetype
          True if the object being edited is a spawn archetype,
          false if it's a starting object.

        \param newValue
          The new value to write to the component array.

        \param chainUndo
          Whether undo chaining is enabled for this command.
      */
      /**************************************************************/
      EditComponentArray(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& objectName,
        const std::string& componentArrayName,
        bool isSpawnArchetype,
        const rttr::variant& newValue,
        bool chainUndo);

    private:
      /**************************************************************/
      /*!
        \brief
          Writes a new value to a component array.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Undoes the command.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Redoes the command.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string objectName_;
      std::string componentArrayName_;
      bool isSpawnArchetype_;

      rttr::variant newValue_;
      rttr::variant oldValue_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditStartingObjectComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////