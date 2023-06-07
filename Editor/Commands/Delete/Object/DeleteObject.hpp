/* ======================================================================== */
/*!
 * \file            DeleteObject.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Removes an object archetype from the scene and the archetype manager.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DeleteObject_BARRAGE_H
#define DeleteObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp>

namespace Barrage
{
  //! Removes an object archetype from the scene and the archetype manager
  class DeleteObject : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the DeleteObject command.

        \param sceneName
          The name of the scene to remove the object from.

        \param poolName
          The name of the pool to remove the object from.

        \param objectName
          The name of the object to remove.
      */
      /**************************************************************/
      DeleteObject(
        const std::string& sceneName, 
        const std::string& poolName, 
        const std::string& objectName);

      /**************************************************************/
      /*!
        \brief
          Deallocates resources.
      */
      /**************************************************************/
      ~DeleteObject();

    private:
      /**************************************************************/
      /*!
        \brief
          Removes the object archetype from the scene and the 
          archetype manager.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Adds the object archetype back to the scene and the 
          archetype manager.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Removes the object archetype from the scene and the 
          archetype manager.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string objectName_;

      unsigned undoIndex_;
      ObjectArchetype* undoArchetype_;
  };
}


////////////////////////////////////////////////////////////////////////////////
#endif // DeleteObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////