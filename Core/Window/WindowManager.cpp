/* ======================================================================== */
/*!
 *
 * \file            WindowManager.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
    Manages the game window.
 */
 /* ======================================================================== */

#include "stdafx.h"
#include "WindowManager.hpp"

#include <stdexcept>

namespace Barrage
{
  WindowManager::WindowManager() :
    window_(nullptr)
  {
  }

  void WindowManager::Initialize()
  {
    // Initialize GLFW
    if (!glfwInit())
    {
      throw std::runtime_error("ERROR: Failed to initialize GLFW.");
    }

    CreateWindow();
  }

  void WindowManager::Shutdown()
  {
    glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
  }

  void WindowManager::SwapBuffers()
  {
    assert(window_);
    glfwSwapBuffers(window_);
  }

  void WindowManager::PollEvents()
  {
    assert(window_);
    glfwPollEvents();
  }

  void WindowManager::Focus()
  {
    assert(window_);
    glfwFocusWindow(window_);
  }

  void WindowManager::Maximize()
  {
    assert(window_);
    glfwMaximizeWindow(window_);
  }

  void WindowManager::SetSize(int width, int height)
  {
    assert(window_);
    glfwSetWindowSize(window_, width, height);
  }

  void WindowManager::SetDecoration(bool decorated)
  {
    assert(window_);
    glfwSetWindowAttrib(window_, GLFW_DECORATED, decorated);
  }

  void WindowManager::SetTitle(const char* title)
  {
    assert(window_);
    glfwSetWindowTitle(window_, title);
  }

  void WindowManager::SetFullScreen()
  {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    int monitorPosX = 0;
    int monitorPosY = 0;
    glfwGetMonitorPos(monitor, &monitorPosX, &monitorPosY);
    SetDecoration(false);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    SetSize(videoMode->width, videoMode->height);
    glfwSetWindowPos(window_, monitorPosX, monitorPosY);
  }

  void WindowManager::SetWindowed()
  {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    int monitorPosX = 0;
    int monitorPosY = 0;
    glfwGetMonitorPos(monitor, &monitorPosX, &monitorPosY);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    SetDecoration(true);
    SetSize(videoMode->width * 3 / 4, videoMode->height * 3 / 4);
    glfwSetWindowPos(window_, monitorPosX + videoMode->width / 8, monitorPosY + videoMode->height / 8);
    Maximize();
  }

  void WindowManager::CreateWindow()
  {
    // Then create the window according to the specifications.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Barrage", nullptr, nullptr);

    if (!window_)
    {
      throw std::runtime_error("Failed to create the window with the given settings.");
    }

    glfwMakeContextCurrent(window_);
  }

  bool WindowManager::IsFocused() const
  {
    assert(window_);
    return glfwGetWindowAttrib(window_, GLFW_FOCUSED);
  }

  bool WindowManager::IsClosed() const
  {
    assert(window_);
    return glfwWindowShouldClose(window_);
  }

  GLFWwindow* WindowManager::GetWindowHandle()
  {
    return window_;
  }
}