/* ======================================================================== */
/*!
 * \file            DeleteComponentArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Removes a component array from a pool and removes the corresponding
    component from all objects in that pool.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeleteComponentArray_BARRAGE_H
#define DeleteComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <vector>
#include <string_view>
#include <Objects/Components/BaseClasses/ComponentArray.hpp>

namespace Barrage
{
  //! Removes a component array from a pool and its objects
  class DeleteComponentArray : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param spaceName
          The space containing the pool.

        \param sceneName
          The scene containing the pool.

        \param poolName
          The pool to place the component array in.

        \param componentName
          The component array to add.
      */
      /**************************************************************/
      DeleteComponentArray(
        const std::string& spaceName,
        const std::string& sceneName,
        const std::string& poolName,
        const std::string_view& componentArrayName);

      /**************************************************************/
      /*!
        \brief
          Deallocates resources.
      */
      /**************************************************************/
      ~DeleteComponentArray();

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
      std::string sceneName_;
      std::string poolName_;
      std::string_view componentArrayName_;

      unsigned undoIndex_;
      std::vector<ComponentArray*> undoComponentArrays_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////