/* ======================================================================== */
/*!
 * \file            HierarchyWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Displays all pools in current game scene.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef HierarchyWidget_BARRAGE_H
#define HierarchyWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Widget.hpp"
#include <string_view>

namespace Barrage
{
  //! Displays all pools in current game scene
  class HierarchyWidget : public Widget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs the hierarchy widget with references to the
          data it's allowed to see/change in the editor and engine.

        \param editorData
          Runtime settings and data for the editor.

        \param engine
          The currently running engine.
      */
      /**************************************************************/
      HierarchyWidget(EditorData& editorData, Engine& engine);

      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      void UseWidget();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // HierarchyWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////