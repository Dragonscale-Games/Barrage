/* ======================================================================== */
/*!
 * \file            DeleteTag.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a tag from a pool archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeleteTag_BARRAGE_H
#define DeleteTag_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <string_view>

namespace Barrage
{
  //! Removes a tag from a pool archetype.
  class DeleteTag : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param sceneName
          The scene containing the pool.

        \param poolName
          The pool to remove the tag from.

        \param tag
          The tag to remove.
      */
      /**************************************************************/
      DeleteTag(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string_view& tag);

    private:
      /**************************************************************/
      /*!
        \brief
          Deletes a tag from a pool archetype.

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
      std::string_view tag_;

      unsigned undoIndex_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteTag_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////