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

#include <Objects/Archetypes/PoolArchetype/PoolArchetype.hpp>
#include <Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp>

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

      static ImVec2 GetSize();

    private:
      static void SceneGUI();

      static bool PoolGUI(PoolArchetype* poolArchetype);

      static bool ObjectGUI(const std::string poolName, ObjectArchetype* objectArchetype, bool isSpawnArchetype = false);
      
      /**************************************************************/
      /*!
        \brief
          Deselects all items selected in the hierarchy.
      */
      /**************************************************************/
      static void DeselectAll();

      static ImVec2 size_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // HierarchyWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////