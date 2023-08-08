/* ======================================================================== */
/*!
 *
 * \file            WindowManager.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the windowing system used by the engine.
 * This does not create the rendering context for the window,
 * that is the renderer's job.
 */
 /* ======================================================================== */

//  ===========================================================================
// Includes
//  ===========================================================================
#include <stdafx.h>
#include <stdexcept>

#include "WindowManager.hpp"

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

  void WindowManager::SetFramebufferSizeCallback(GLFWframebuffersizefun function)
  {
    assert(window_);
    glfwSetFramebufferSizeCallback(window_, function);
  }

  void WindowManager::SetUserPointer(void* data)
  {
    assert(window_);
    glfwSetWindowUserPointer(window_, data);
  }
}