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

#include "Widgets/Hierarchy/HierarchyWidget.hpp"
#include "Widgets/Inspector/InspectorWidget.hpp"
#include "Widgets/Log/LogWidget.hpp"
#include "Widgets/MainMenu/MainMenuWidget.hpp"

#include <string_view>

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
      */
      /**************************************************************/
      void Run();

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

      /**************************************************************/
      /*!
        \brief
          Gets the editor's log widget.

        \return
          Returns a reference to the editor's log widget.
      */
      /**************************************************************/
      LogWidget& Log();

    private:
      /**************************************************************/
      /*!
        \brief
          Initializes Barrage engine and editor systems.
      */
      /**************************************************************/
      void Initialize();

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
          Adds the main editor widget to the window.
      */
      /**************************************************************/
      void UseEditorWidget();

      /**************************************************************/
      /*!
        \brief
          Handles keyboard shortcuts and other keyboard input.
      */
      /**************************************************************/
      void HandleKeyboard();

    private:
      Engine engine_;             //!< Barrage game engine
      GUI gui_;                   //!< Contains all widgets/user controls
      EditorData data_;           //!< Public settings and data for the editor
      CommandQueue commandQueue_; //!< Allows commands to be sent and processed

      HierarchyWidget hierarchy_; //!< Shows the hierarchy widget
      InspectorWidget inspector_; //!< Shows the inspector widget
      LogWidget log_;             //!< Shows the log widget
      MainMenuWidget mainMenu_;   //!< Shows the main menu bar

      long long repeatTimer_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Editor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////