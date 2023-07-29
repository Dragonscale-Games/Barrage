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

#include <Engine/Engine.hpp>
#include "EditorData.hpp"
#include "GUI/GUI.hpp"
#include "Commands/CommandQueue.hpp"

#include <string>
#include <string_view>

#include "Widgets/Windows/Log/LogWidget.hpp"

namespace Barrage
{
	//! Editor for Barrage Engine
  class Editor
	{
    public:   
      static Editor* Instance;
      
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      Editor();

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

      /**************************************************************/
      /*!
        \brief
          Gets the public editor data that widgets can modify.

        \return
          Returns a reference to the editor's public data.
      */
      /**************************************************************/
      EditorData& Data();

      /**************************************************************/
      /*!
        \brief
          Gets the editor's command queue.

        \return
          Returns a reference to the editor's command queue.
      */
      /**************************************************************/
      CommandQueue& Command();

      bool CreateProject(const std::string& name);

      bool OpenProject();

      bool SaveProject(const std::string& directory);

    private:
      Engine engine_;             //!< Barrage game engine
      GUI gui_;                   //!< Contains all widgets/user controls
      EditorData data_;           //!< Public settings and data for the editor
      CommandQueue commandQueue_; //!< Allows commands to be sent and processed

      long long repeatTimer_;

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

      /**************************************************************/
      /*!
        \brief
          Handles keyboard shortcuts and other keyboard input.
      */
      /**************************************************************/
      void HandleKeyboard();

      bool OpenProjectInternal(const std::string& path);
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Editor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////