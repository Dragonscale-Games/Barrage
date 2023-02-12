/* ======================================================================== */
/*!
 * \file            CreatePool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Creates a new (empty) pool archetype and adds that archetype to the scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef CreatePool_BARRAGE_H
#define CreatePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Commands/Command.hpp>

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

    private:
      /**************************************************************/
      /*!
        \brief
          Creates the pool archetype and adds it to the scene.

        \return
          Returns true if the value change was successful, returns
          false otherwise.
      */
      /**************************************************************/
      bool Execute() override;

      /**************************************************************/
      /*!
        \brief
          Removes the pool archetype from the scene and deletes it.
      */
      /**************************************************************/
      void Undo() override;

    private:
      std::string spaceName_;
      std::string sceneName_;
      std::string poolName_;
  };
}


////////////////////////////////////////////////////////////////////////////////
#endif // CreatePool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////