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
#include "GUI/GUI.hpp"

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
          TEMPORARY: Just testing out ImGui
      */
      /**************************************************************/
      void MakeTestWidget();

    private:
      Engine engine_;       //!< Barrage game engine
      GUI gui_;             //!< Contains all widgets/user controls
      long long frameTime_; //!< TEMPORARY: holds the current frame time in milliseconds
      unsigned numTicks_;   //!< TEMPORARY: holds number of ticks that should be performed this frame
      bool statePaused_;    //!< TEMPORARY: stores whether game state is paused
      bool isRunning_;      //!< Keeps track of whether the editor is running
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Editor_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////