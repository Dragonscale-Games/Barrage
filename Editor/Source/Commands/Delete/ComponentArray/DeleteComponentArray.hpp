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
#include <unordered_map>
#include <string_view>
#include <Objects/Components/BaseClasses/ComponentArray.hpp>
#include <Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp>

namespace Barrage
{
  typedef std::unordered_map<std::string, ComponentArray*> UndoComponentArrayMap;
  
  //! Removes a component array from a pool and its objects
  class DeleteComponentArray : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param sceneName
          The scene containing the pool.

        \param poolName
          The pool to place the component array in.

        \param componentName
          The component array to add.
      */
      /**************************************************************/
      DeleteComponentArray(
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
          Deletes component arrays from a pool archetype.

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

      /**************************************************************/
      /*!
        \brief
          Replaces the original component arrays on each object in
          the input vector.

        \param objects
          The objects to replace the component array on.
      */
      /**************************************************************/
      void ReplaceComponentArraysOnObjects(const std::vector<ObjectArchetype*>& objects);

      /**************************************************************/
      /*!
        \brief
          Removes the component array from each object in the input
          vector.

        \param objects
          The objects to remove the component array from.
      */
      /**************************************************************/
      void RemoveComponentArraysFromObjects(const std::vector<ObjectArchetype*>& objects);

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string_view componentArrayName_;

      unsigned undoIndex_;
      UndoComponentArrayMap undoComponentArrays_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////