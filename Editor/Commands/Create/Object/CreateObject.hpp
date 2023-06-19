/* ======================================================================== */
/*!
 * \file            CreateObject.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new (empty) object archetype and adds that object to a pool
   in the scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreateObject_BARRAGE_H
#define CreateObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <stack>
#include <Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp>

namespace Barrage
{
  //! Creates an object and adds it to a pool in the scene
  class CreateObject : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the CreateObject command.

        \param sceneName
          The name of the scene to place the object in.

        \param poolName
          The name of the pool to create the object in.

        \param isStartingObject
          True if the object being created is a starting object,
          false if it's a spawn archetype.
      */
      /**************************************************************/
      CreateObject(const std::string& sceneName, const std::string& poolName, bool isStartingObject);

      /**************************************************************/
      /*!
        \brief
          Deallocates resources.
      */
      /**************************************************************/
      ~CreateObject();

    private:
      /**************************************************************/
      /*!
        \brief
          Creates the object archetype and adds it to a pool in the 
          scene.

        \return
          Returns true if the command was successful, returns false
          if the command had no effect.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Removes the object archetype from the pool in the scene 
          and removes it from the archetype manager.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Adds the previously removed object archetype back to the
          archetype manager and the pool in the scene.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string objectName_;
      bool isStartingObject_;

      ObjectArchetype* redoArchetype_;
  };
}


////////////////////////////////////////////////////////////////////////////////
#endif // CreateObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////