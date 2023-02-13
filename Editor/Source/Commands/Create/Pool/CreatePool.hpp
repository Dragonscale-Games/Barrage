/* ======================================================================== */
/*!
 * \file            CreatePool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new (empty) pool archetype and adds that pool to the scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreatePool_BARRAGE_H
#define CreatePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <stack>
#include <Objects/Archetypes/PoolArchetype/PoolArchetype.hpp>

namespace Barrage
{
  //! Creates a pool archetype and adds it to the scene
  class CreatePool : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the CreatePool command.

        \param spaceName
          The name of the space to construct the pool in.

        \param sceneName
          The scene to place the pool in.
      */
      /**************************************************************/
      CreatePool(const std::string& spaceName, const std::string& sceneName);

      /**************************************************************/
      /*!
        \brief
          Deallocates resources.
      */
      /**************************************************************/
      ~CreatePool();

    private:
      /**************************************************************/
      /*!
        \brief
          Creates the pool archetype and adds it to the scene.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Removes the pool archetype from the scene and the archetype
          manager.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Adds the previously removed pool archetype back to the 
          archetype manager and the scene.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string spaceName_;
      std::string sceneName_;
      std::string poolName_;

      PoolArchetype* redoArchetype_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreatePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////