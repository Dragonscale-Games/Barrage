/* ======================================================================== */
/*!
 * \file            RenamePool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Renames a pool.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RenamePool_BARRAGE_H
#define RenamePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>

namespace Barrage
{
  //! Renames a pool
  class RenamePool : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the RenamePool command.

        \param sceneName
          The name of the scene the pool lives in.

        \param poolName
          The name of the pool to rename.

        \param newName
          The new name of the pool.
      */
      /**************************************************************/
      RenamePool(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& newName);

    private:
      /**************************************************************/
      /*!
        \brief
          Renames the pool.

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
      std::string newName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RenamePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////