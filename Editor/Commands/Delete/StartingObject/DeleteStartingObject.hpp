/* ======================================================================== */
/*!
 * \file            DeleteStartingObject.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes an starting object from its pool.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeleteStartingObject_BARRAGE_H
#define DeleteStartingObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/ObjectArchetype.hpp>

namespace Barrage
{
  //! Removes an starting object from its pool
  class DeleteStartingObject : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the DeleteStartingObject command.

        \param sceneName
          The name of the scene to remove the object from.

        \param poolName
          The name of the pool to remove the object from.

        \param startingObjectName
          The name of the object to remove.
      */
      /**************************************************************/
      DeleteStartingObject(
        const std::string& sceneName, 
        const std::string& poolName, 
        const std::string& startingObjectName);

    private:
      /**************************************************************/
      /*!
        \brief
          Removes the starting object from its pool.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Adds the starting object back to its pool.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Removes the starting object from its pool.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string startingObjectName_;

      ObjectArchetype undoArchetype_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DeleteStartingObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////