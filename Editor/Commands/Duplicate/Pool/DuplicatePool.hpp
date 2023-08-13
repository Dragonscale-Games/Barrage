/* ======================================================================== */
/*!
 * \file            DuplicatePool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Duplicates an existing pool archetype in the scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DuplicatePool_BARRAGE_H
#define DuplicatePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/PoolArchetype/PoolArchetype.hpp>

namespace Barrage
{
  //! Duplicates an existing pool archetype in the scene
  class DuplicatePool : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the DuplicatePool command.

        \param sceneName
          The scene to place the pool in.

        \param poolName
          The pool to duplicate.
      */
      /**************************************************************/
      DuplicatePool(const std::string& sceneName, const std::string& poolName);

      /**************************************************************/
      /*!
        \brief
          Deallocates resources.
      */
      /**************************************************************/
      ~DuplicatePool();

    private:
      /**************************************************************/
      /*!
        \brief
          Duplicates an existing pool archetype in the scene.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Removes the duplicated pool archetype from the scene.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Adds the previously removed pool archetype back to the
          scene.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;

      PoolArchetype* redoArchetype_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DuplicatePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////