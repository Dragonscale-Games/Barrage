/* ======================================================================== */
/*!
 * \file            CreateComponentArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a component array to a pool archetype and adds the corresponding
   component to each of the pool's object archetypes.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreateComponentArray_BARRAGE_H
#define CreateComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Components/BaseClasses/ComponentArray.hpp>
#include <vector>
#include <string_view>

namespace Barrage
{
  //! Adds a component array to a pool and its objects
  class CreateComponentArray : public Command
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
      CreateComponentArray(
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
      ~CreateComponentArray();

    private:
      /**************************************************************/
      /*!
        \brief
          Adds a component array to a pool archetype and adds the
          corresponding component to each of the pool's object
          archetypes.

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

      std::vector<ComponentArray*> redoComponentArrays_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreateComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////