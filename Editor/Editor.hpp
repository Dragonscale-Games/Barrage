/* ======================================================================== */
/*!
 * \file            Editor.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Editor for Barrage Engine. Allows the user to create bullet hell games.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Editor_BARRAGE_H
#define Editor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Engine.hpp"
#include "GUI/GUI.hpp"

namespace Barrage
{
  //! Editor for Barrage Engine
  class Editor
  {
    public:
      Editor(Editor const&) = delete;
      Editor(Editor&&) = delete;
      Editor& operator=(Editor const&) = delete;
      Editor& operator=(Editor&&) = delete;

      /**************************************************************/
      /*!
        \brief
          Gets the instance of the (singleton) editor.

        \return
          Returns a reference to the editor instance.
      */
      /**************************************************************/
      static Editor& Get();

      /**************************************************************/
      /*!
        \brief
          Calling this runs the editor.

        \param projectPath
          The path of the project to open on startup. If empty,
          editor GUI will prompt user to open a project.
      */
      /**************************************************************/
      void Run(const std::string& projectPath = std::string());

      /**************************************************************/
      /*!
        \brief
          Gets the editor's GUI manager.

        \return
          Returns a reference to the editor's GUI manager.
      */
      /**************************************************************/
      GUI& Gui();

    private:
      Engine& engine_;            //!< Barrage game engine
      GUI gui_;                   //!< Contains all widgets/user controls
      bool isRunning_;

      /**************************************************************/
      /*!
        \brief
          Private constructor for singleton class.
      */
      /**************************************************************/
      Editor();

      /**************************************************************/
      /*!
        \brief
          Initializes Barrage engine and editor systems.
      */
      /**************************************************************/
      void Initialize(const std::string& projectPath = std::string());

      /**************************************************************/
      /*!
        \brief
          Updates main editor loop.
      */
      /**************************************************************/
      void Update();

      /**************************************************************/
      /*!
        \brief
          Shuts down Barrage engine and editor systems.
      */
      /**************************************************************/
      void Shutdown();

      /**************************************************************/
      /*!
        \brief
          Displays all editor widgets.
      */
      /**************************************************************/
      void UseWidgets();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Editor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////