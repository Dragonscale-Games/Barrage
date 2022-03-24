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
  }

  void GUI::EndWidgets()
  {
    ImGui::Render();
  }

  void GUI::DrawWidgets()
  {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void GUI::Shutdown()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();
  }
}