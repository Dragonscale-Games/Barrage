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

        \param spaceName
          The space containing the pool.

        \param poolName
          The pool to remove the component from.

        \param componentName
          The component to remove.
      */
      /**************************************************************/
      DeleteSharedComponent(
        const std::string& spaceName,
        const std::string& poolName,
        const std::string_view& componentName);

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
      std::string spaceName_;
      std::string poolName_;
      std::string_view componentName_;

      SharedComponent* undoComponent_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteSharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////