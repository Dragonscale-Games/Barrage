/* ======================================================================== */
/*!
 * \file            GUI.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   ImGui wrapper class.
 */
/* ======================================================================== */

#include "GUI.hpp"
#include <GLFW/glfw3.h>

namespace Barrage
{
  GUI::GUI()
  {
  }

  void GUI::Initialize(GLFWwindow* window)
  {
    IMGUI_CHECKVERSION();
    if (!ImGui::CreateContext())
      return;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
      return;

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
      return;
  }

  void GUI::StartWidgets()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    BeginDockingSpace();
  }

  void GUI::EndWidgets()
  {
    EndDockingSpace();
    
    ImGui::Render();
  }

  void GUI::DrawWidgets()
  {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }
  }

  void GUI::Shutdown()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();
  }

  void GUI::BeginDockingSpace()
  {
    // Taken from imgui_demo.cpp
    ImGuiWindowFlags windowFlags = 0;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    windowFlags |= ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    windowFlags |= ImGuiWindowFlags_NoNavFocus;
    windowFlags |= ImGuiWindowFlags_NoBackground;
    windowFlags |= ImGuiWindowFlags_NoTitleBar;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("Barrage Editor - Docking Space", nullptr, windowFlags);
    ImGui::PopStyleVar(3);

    // Start a dockspace.
    const ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockingID = ImGui::GetID("Barrage Editor - Docking Space");
      ImGuiDockNodeFlags flags = ImGuiDockNodeFlags_NoDockingInCentralNode
        | ImGuiDockNodeFlags_PassthruCentralNode;
      ImGui::DockSpace(dockingID, ImVec2(0.0f, 0.0f), flags);
    }
  }

  void GUI::EndDockingSpace()
  {
    ImGui::End();
  }
}