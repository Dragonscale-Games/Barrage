/* ======================================================================== */
/*!
 * \file            CreateStartingObject.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new object archetype and adds it as a starting object to a pool 
   in the scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreateStartingObject_BARRAGE_H
#define CreateStartingObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Archetypes/ObjectArchetype.hpp>

namespace Barrage
{
  //! Creates a starting object and adds it to a pool in the scene
  class CreateStartingObject : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the CreateStartingObject command.

        \param sceneName
          The name of the scene to place the object in.

        \param poolName
          The name of the pool to create the object in.
      */
      /**************************************************************/
      CreateStartingObject(const std::string& sceneName, const std::string& poolName);

    private:
      /**************************************************************/
      /*!
        \brief
          Creates the starting object and adds it to a pool in the 
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
          Removes the starting object from the pool in the scene 
          and removes it from the archetype manager.
      */
      /**************************************************************/
      void Undo() override;

      /**************************************************************/
      /*!
        \brief
          Adds the previously removed starting object back to the
          archetype manager and the pool in the scene.
      */
      /**************************************************************/
      void Redo() override;

    private:
      std::string sceneName_;
      std::string poolName_;
      std::string startingObjectName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreateStartingObject_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////