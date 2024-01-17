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
#include "Data/EditorData.hpp"
#include "GUI/GUI.hpp"
#include "Commands/CommandQueue.hpp"

#include "Widgets/Windows/Log/LogWidget.hpp"

namespace Barrage
{
  //! Editor for Barrage Engine
  class Editor
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Private constructor for singleton class.
      */
      /**************************************************************/
      Editor();
      
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

      static void BuildGame(bool runExecutable = false);

    private:
      Engine engine_;             //!< Barrage game engine
      CommandQueue commandQueue_; //!< Allows commands to be sent and processed
      EditorData data_;           //!< Public settings and data for the editor
      GUI gui_;                   //!< Contains all widgets/user controls

      long long repeatTimer_;
      GLuint timeQueryID_;

      static Editor* instance_;

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