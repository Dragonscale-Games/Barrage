/* ======================================================================== */
/*!
 * \file            InspectorWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit components for pools and game objects.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef InspectorWidget_BARRAGE_H
#define InspectorWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Widget.hpp"
#include <string_view>

namespace Barrage
{
  //! Allows user to modify components
  class InspectorWidget : public Widget
  {
    public:
      /**************************************************************/
        /*!
          \brief
            Constructs the inspector widget with references to the 
            data it's allowed to see/change in the editor and engine.

          \param editorData
            Runtime settings and data for the editor.

          \param engine
            The currently running engine.
        */
        /**************************************************************/
      InspectorWidget(EditorData& editorData, Engine& engine);

      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      void UseWidget() override;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // InspectorWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////