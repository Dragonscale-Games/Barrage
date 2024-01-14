/* ======================================================================== */
/*!
 * \file            EditCapacity.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Edits a pool archetype's capacity.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef EditCapacity_BARRAGE_H
#define EditCapacity_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <rttr/variant.h>

namespace Barrage
{
  //! Edits a pool archetype's capacity
  class EditCapacity : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param sceneName
          The scene containing the relevant pool.

        \param poolName
          The pool archetype to edit.

        \param newCapacity
          The pool's new capacity.

        \param chainUndo
          Whether undo chaining is enabled for this command.
      */
      /**************************************************************/
      EditCapacity(
        const std::string& sceneName,
        const std::string& poolName,
        unsigned newCapacity,
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

      unsigned newValue_;
      unsigned oldValue_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EditCapacity_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////