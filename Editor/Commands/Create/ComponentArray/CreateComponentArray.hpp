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
#include <Objects/Archetypes/ObjectArchetype.hpp>
#include <Objects/Components/ComponentArray.hpp>
#include <unordered_map>

namespace Barrage
{
  typedef std::unordered_map<std::string, ComponentArray*> RedoComponentArrayMap;
  
  //! Adds a component array to a pool and its objects
  class CreateComponentArray : public Command
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
      CreateComponentArray(
        const std::string& sceneName,
        const std::string& poolName,
        const std::string& componentArrayName);

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

      /**************************************************************/
      /*!
        \brief
          Adds the component array to each object.

        \param objects
          The objects to add the component array to.
      */
      /**************************************************************/
      bool AddComponentArraysToObjects(ObjectArchetypeMap& objects);

      /**************************************************************/
      /*!
        \brief
          Removes the component array from each object.

        \param objects
          The objects to remove the component array from.
      */
      /**************************************************************/
      void RemoveComponentArraysFromObjects(ObjectArchetypeMap& objects);

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string componentArrayName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreateComponentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////