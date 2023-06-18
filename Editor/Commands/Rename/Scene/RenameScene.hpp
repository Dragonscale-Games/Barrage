/* ======================================================================== */
/*!
 * \file            RenameScene.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RenameScene_BARRAGE_H
#define RenameScene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>

namespace Barrage
{
  //! Renames a scene
  class RenameScene : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the RenameScene command.

        \param sceneName
          The name of the scene to rename.

        \param newName
          The new name of the scene.
      */
      /**************************************************************/
      RenameScene(
        const std::string& sceneName,
        const std::string& newName);

    private:
      /**************************************************************/
      /*!
        \brief
          Renames the scene.

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
      std::string newName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RenameScene_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////