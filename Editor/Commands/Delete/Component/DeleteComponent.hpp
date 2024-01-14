/* ======================================================================== */
/*!
 * \file            DeleteComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a component from a pool archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeleteComponent_BARRAGE_H
#define DeleteComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Components/Component.hpp>

namespace Barrage
{
  //! Removes a component from a pool archetype.
  class DeleteComponent : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param sceneName
          The scene containing the pool.

        \param poolName
          The pool to remove the component from.

        \param componentName
          The component to remove.
      */
      /**************************************************************/
      DeleteComponent(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& componentName);

    private:
      /**************************************************************/
      /*!
        \brief
          Deletes a component from a pool archetype.

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
      std::string componentName_;

      ComponentDeepPtr undoComponent_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////