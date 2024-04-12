/* ======================================================================== */
/*!
 * \file            CreateComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a component to a pool archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreateComponent_BARRAGE_H
#define CreateComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Components/Component.hpp>

namespace Barrage
{
  //! Adds a component to a pool archetype
  class CreateComponent : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.

        \param poolName
          The pool to place the component in. 

        \param componentName
          The component to add.
      */
      /**************************************************************/
      CreateComponent(
        const std::string& sceneName, 
        const std::string& poolName, 
        const std::string& componentName);

    private:
      /**************************************************************/
      /*!
        \brief
          Adds a component to a pool archetype.

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
      std::string sceneName_;
      std::string poolName_;      
      std::string componentName_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreateComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////