/* ======================================================================== */
/*!
 * \file            EditSharedComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Edits the value of a shared component in an pool archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef EditComponent_BARRAGE_H
#define EditComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <rttr/variant.h>
#include <string_view>

namespace Barrage
{
  //! Edits the value of a component in an pool archetype
  class EditComponent : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param sceneName
          The scene containing the relevant pool.

        \param poolName
          The pool archetype containing the component to edit.

        \param componentName
          The name of the component to edit.

        \param newValue
          The new value to write to the component.

        \param chainUndo
          Whether undo chaining is enabled for this command.
      */
      /**************************************************************/
      EditComponent(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string_view& componentName,
        const rttr::variant& newValue,
        bool chainUndo);

    private:
      /**************************************************************/
      /*!
        \brief
          Writes a new value to a component.

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
      std::string_view componentName_;

      rttr::variant newValue_;
      rttr::variant oldValue_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////