/* ======================================================================== */
/*!
 * \file            CreateTag.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a tag to a pool archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreateTag_BARRAGE_H
#define CreateTag_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>

namespace Barrage
{
  //! Adds a tag to a pool archetype
  class CreateTag : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param poolName
          The pool to add the tag to.

        \param tag
          The tag to add.
      */
      /**************************************************************/
      CreateTag(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& tag);

    private:
      /**************************************************************/
      /*!
        \brief
          Adds a tag to a pool archetype.

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
      std::string tag_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreateTag_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////