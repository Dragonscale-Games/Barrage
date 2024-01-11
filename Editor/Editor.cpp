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

namespace Barrage
{
  Editor& Editor::Get()
  {
    static Editor instance;
    return instance;
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

  Editor::Editor() :
    engine_(Engine::Get()),
    gui_(),
    isRunning_(false)
  {
  }

  void Editor::Initialize(const std::string& projectPath)
  {
    engine_.Initialize();
    gui_.Initialize(engine_.Window().GetWindowHandle());
    engine_.Window().Maximize();
    engine_.Frames().SetVsync(true);

    engine_.Spaces().AddSpace("Editor Space");
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
  }

  void Editor::UseWidgets()
  {
    
  }
}