/* ======================================================================== */
/*!
 * \file            CreateSharedComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Adds a shared component to a pool archetype.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreateSharedComponent_BARRAGE_H
#define CreateSharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>
#include <Objects/Components/BaseClasses/SharedComponent.hpp>
#include <string_view>

namespace Barrage
{
  //! Adds a shared component to a pool archetype
  class CreateSharedComponent : public Command
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the command.
          
        \param spaceName
          The space containing the pool.

        \param poolName
          The pool to place the component in. 

        \param componentName
          The component to add.
      */
      /**************************************************************/
      CreateSharedComponent(
        const std::string& spaceName, 
        const std::string& poolName, 
        const std::string_view& componentName);

      /**************************************************************/
      /*!
        \brief
          Deallocates resources.
      */
      /**************************************************************/
      ~CreateSharedComponent();

    private:
      /**************************************************************/
      /*!
        \brief
          Adds a shared component to a pool archetype.

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
      std::string spaceName_;     
      std::string poolName_;      
      std::string_view componentName_;

      SharedComponent* redoComponent_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // CreateSharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////