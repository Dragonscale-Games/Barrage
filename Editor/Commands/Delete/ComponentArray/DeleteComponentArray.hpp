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
#include <Objects/Components/ComponentArray.hpp>
#include <Objects/Archetypes/ObjectArchetype.hpp>

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
        const std::string& componentArrayName);

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
          Removes the component array from each object.

        \param objects
          The objects to remove the component array from.

        \param arrayMap
          The map to store the component arrays in.
      */
      /**************************************************************/
      void RemoveComponentArraysFromObjects(ObjectArchetypeMap& objects, ComponentArrayMap& arrayMap);

      /**************************************************************/
      /*!
        \brief
          Replaces the original component arrays on each object.

        \param objects
          The objects to replace the component array on.

        \param arrayMap
          The map the component arrays are stored in.
      */
      /**************************************************************/
      void ReplaceComponentArraysOnObjects(ObjectArchetypeMap& objects, ComponentArrayMap& arrayMap);

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string componentArrayName_;

      ComponentArrayMap undoStartingObjectArrays_;
      ComponentArrayMap undoSpawnArchetypeArrays_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////