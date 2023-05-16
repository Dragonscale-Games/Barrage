/* ======================================================================== */
/*!
 * \file            DeleteSharedComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a shared component from a pool archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeleteSharedComponent_BARRAGE_H
#define DeleteSharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Components/BaseClasses/SharedComponent.hpp>
#include <string_view>

namespace Barrage
{
  //! Removes a shared component from a pool archetype.
  class DeleteSharedComponent : public Command
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

        \param sharedComponentName
          The shared component to remove.
      */
      /**************************************************************/
      DeleteSharedComponent(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string_view& sharedComponentName);

      /**************************************************************/
      /*!
        \brief
          Deallocates resources.
      */
      /**************************************************************/
      ~DeleteSharedComponent();

    private:
      /**************************************************************/
      /*!
        \brief
          Deletes a shared component from a pool archetype.

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

      SharedComponent* undoComponent_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteSharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////