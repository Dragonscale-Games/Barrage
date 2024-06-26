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

#include "Scenes/Scene.hpp"

#include <imgui/imgui.h>

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
      static void SceneGUI();

      static bool PoolGUI(PoolArchetype& poolArchetype);

      static bool ObjectGUI(const std::string poolName, ObjectArchetype& objectArchetype, bool isSpawnArchetype);

      static void SelectStartingObject(const std::string name);

      static void SelectSpawnArchetype(const std::string name);

      static void DeselectAll();
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // HierarchyWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////