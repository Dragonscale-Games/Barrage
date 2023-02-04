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

#include "Widgets/Hierarchy/HierarchyWidget.hpp"
#include "Widgets/Inspector/InspectorWidget.hpp"

#include <string_view>

namespace Barrage
{
	//! Editor for Barrage Engine
  class Editor
	{
    public:   
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

    private:
      Engine engine_;   //!< Barrage game engine
      GUI gui_;         //!< Contains all widgets/user controls
      EditorData data_; //!< Runtime settings and data for the editor
      bool isRunning_;  //!< Keeps track of whether the editor is running

      HierarchyWidget hierarchy_; //!< Shows the hierarchy widget
      InspectorWidget inspector_; //!< Shows the inspector widget
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Editor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////