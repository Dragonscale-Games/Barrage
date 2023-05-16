/* ======================================================================== */
/*!
 * \file            DemoInitialization.hpp
 * \par             Demo Game
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Sets up scene and space for the demo game.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef DemoInitialization_DEMO_H
#define DemoInitialization_DEMO_H
////////////////////////////////////////////////////////////////////////////////

#include <Engine/Engine.hpp>

namespace Demo
{
  Barrage::Space* CreateDemoSpace();

  Barrage::Scene* CreateDemoScene();

  void CreatePlayerArchetypes(Barrage::Scene& scene);

  void CreateBulletArchetypes(Barrage::Scene& scene);

  void CreateSpawnerArchetypes(Barrage::Scene& scene);
}

////////////////////////////////////////////////////////////////////////////////
#endif // DemoInitialization_DEMO_H
////////////////////////////////////////////////////////////////////////////////