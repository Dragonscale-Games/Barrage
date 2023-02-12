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

#include <imgui/imgui.h>
#include <string_view>

namespace Barrage
{
  //! Displays all pools in current game scene
  class HierarchyWidget 
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds the widget to the window.
      */
      /**************************************************************/
      static void Use();

    private:
      /**************************************************************/
      /*!
        \brief
          Deselects all items selected in the hierarchy.
      */
      /**************************************************************/
      static void DeselectAll();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // HierarchyWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////