/* ======================================================================== */
/*!
 * \file            Editor.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here>

 */
 /* ======================================================================== */

#include "stdafx.h"

#include "Editor.hpp"

#include "Widgets/Windows/Game/GameWidget.hpp"
#include "Widgets/Windows/Hierarchy/HierarchyWidget.hpp"
#include "Widgets/Windows/Inspector/InspectorWidget.hpp"
#include "Widgets/Windows/Log/LogWidget.hpp"
#include "Widgets/Windows/Performance/PerformanceWidget.hpp"
#include "Widgets/Windows/Timeline/TimelineWidget.hpp"

#include "Widgets/MainMenu/MainMenuWidget.hpp"

namespace Barrage
{
  Editor* Editor::instance_ = nullptr;
  
  Editor::Editor() :
    isRunning_(false),
    engine_(),
    gui_()
  {
  }
  
  Editor& Editor::Get()
  {
    return *instance_;
  }
  
  void Editor::Run(const std::string& projectPath)
  {
    if (!isRunning_)
    {
      isRunning_ = true;

      Initialize(projectPath);

      while (isRunning_)
      {
        Update();
      }

      Shutdown();

      isRunning_ = false;
    }
  }

  GUI& Editor::Gui()
  {
    return gui_;
  }

  void Editor::Initialize(const std::string& projectPath)
  {
    instance_ = this;
    engine_.Initialize();
    gui_.Initialize(engine_.Window().GetWindowHandle());
    engine_.Window().Maximize();
    engine_.Frames().SetVsync(true);

    engine_.Spaces().AddSpace("Editor Space");
    Space& editorSpace = *engine_.Spaces().GetSpace("Editor Space");
    editorSpace.AllowSceneChangesDuringUpdate(false);
  }

  void Editor::Update()
  {
    engine_.Frames().StartFrame();

    engine_.Input().Reset();
    engine_.Window().PollEvents();

    // update game

    gui_.StartWidgets();
    UseWidgets();
    gui_.EndWidgets();

    engine_.Graphics().GetFramebuffer().BindFramebuffer();
    engine_.Graphics().ClearBackground();
    engine_.Spaces().Draw();
    engine_.Graphics().GetFramebuffer().UnbindFramebuffer();
    gui_.DrawWidgets();
    engine_.Window().SwapBuffers();

    if (engine_.Window().IsClosed())
    {
      isRunning_ = false;
    }

    engine_.Frames().EndFrame(!engine_.Window().IsFocused());
  }

  void Editor::Shutdown()
  {
    gui_.Shutdown();

    engine_.Shutdown();
    instance_ = nullptr;
  }

  void Editor::UseWidgets()
  {
    GameWidget::Use();
    MainMenuWidget::Use();
    HierarchyWidget::Use();
    InspectorWidget::Use();
    LogWidget::Use();
    PerformanceWidget::Use();
    TimelineWidget::Use();
  }
}