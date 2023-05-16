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
#ifndef EditSharedComponent_BARRAGE_H
#define EditSharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <rttr/variant.h>
#include <string_view>

namespace Barrage
{
  //! Edits the value of a shared component in an pool archetype
  class EditSharedComponent : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param sceneName
          The scene containing the relevant pool.

        \param poolName
          The pool archetype containing the shared component to edit.

        \param sharedComponentName
          The name of the shared component to edit.

        \param newValue
          The new value to write to the shared component.

        \param chainUndo
          Whether undo chaining is enabled for this command.
      */
      /**************************************************************/
      EditSharedComponent(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string_view& sharedComponentName,
        const rttr::variant& newValue,
        bool chainUndo);

    private:
      /**************************************************************/
      /*!
        \brief
          Writes a new value to a shared component.

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
      std::string_view sharedComponentName_;

      rttr::variant newValue_;
      rttr::variant oldValue_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditSharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////