/* ======================================================================== */
/*!
 * \file            DeletePool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes a pool archetype from the scene and the archetype manager.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeletePool_BARRAGE_H
#define DeletePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/PoolArchetype/PoolArchetype.hpp>
#include <Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp>

namespace Barrage
{
  //! Removes a pool archetype from the scene and the archetype manager
  class DeletePool : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the DeletePool command.

        \param spaceName
          The name of the space to remove the pool from.

        \param sceneName
          The name of the scene to remove the pool from.

        \param poolName
          The name of the pool to remove.
      */
      /**************************************************************/
      DeletePool(
        const std::string& spaceName,
        const std::string& sceneName,
        const std::string& poolName);

      ~DeletePool();

    private:
      /**************************************************************/
      /*!
        \brief
          Removes the pool archetype from the scene and the archetype 
          manager.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Adds the pool archetype back to the scene and the archetype 
          manager.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Removes the pool archetype from the scene and the archetype 
          manager.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string spaceName_;
      std::string sceneName_;
      std::string poolName_;

      unsigned undoSceneIndex_;
      //PoolInfo undoScenePool_;
      PoolArchetype* undoPoolArchetype_;
      //ObjectArchetypeMap undoObjectArchetypes_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeletePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////