/* ======================================================================== */
/*
 * MIT License
 * 
 * Copyright (c) 2022 Dragonscale-Games
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
/* ======================================================================== */

/* ======================================================================== */
/*!
 *
 * \file            WindowManager.cpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Defines the windowing system used by the engine.
 * This does not create the rendering context for the window,
 * that is the renderer's job.
 */
 /* ======================================================================== */

//  ===========================================================================
// Includes
//  ===========================================================================
#include <stdexcept>

#include "WindowManager.hpp"
#include <glm/vec2.hpp>

namespace Barrage
{
  WindowManager::WindowManager() :
    window_(nullptr), data_{1440, 720, false, "Barrage"}
  {
  }

  WindowManager::~WindowManager()
  {
  }

  WindowManager::WindowManager(const WindowManager& rhs) :
    window_(nullptr), data_(rhs.data_)
  {
    // If the window exists for the other windowing system
    // then we make one of our own here.
    if (rhs.window_)
    {
      RecreateOsWindow(rhs.data_);
    }
  }

  WindowManager& WindowManager::operator=(const WindowManager& rhs)
  {
    if(this != &rhs)
    {
      // Set all the variables for the data.
      data_ = rhs.data_;

      // If the window exists for 'rhs' then we have to make our own too.
      if (rhs.window_)
      {
        RecreateOsWindow(data_);
      }
    }

    return *this;
  }

  void WindowManager::Initialize(const WindowData& settings)
  {
    // Initialize GLFW
    if(!glfwInit())
    {
      // TODO: Eventually use a logging system to recreate this behaviour.
      throw std::runtime_error("ERROR: Failed to initialize GLFW somehow.");
    }

    RecreateOsWindow(settings);
  }

  void WindowManager::Shutdown()
  {
    glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
  }

  void WindowManager::ResizeToFullscreen()
  {
    // Get the parent monitor the window resides in.
    GLFWmonitor* monitor = GetParentMonitor();
    // Undecorate the window and resize to the window specifcations.
    glm::ivec2 monitorPos;
    const GLFWvidmode* modes = glfwGetVideoMode(monitor);
    // Get the monitor statistics
    glfwGetMonitorPos(monitor, &monitorPos.x, &monitorPos.y);
    // Undecorate the window and resize it to the monitor.
    ChangeDecoration(false);
    Resize(modes->width, modes->height);
    glfwSetWindowPos(window_, monitorPos.x, monitorPos.y);
  }

  void WindowManager::ResizeToWindowed()
  {
    // Get the parent monitor the window resides in.
    GLFWmonitor* monitor = GetParentMonitor();
    // Undecorate the window and resize to the window specifcations.
    glm::ivec2 monitorPos;
    // Get the monitor statistics
    glfwGetMonitorPos(monitor, &monitorPos.x, &monitorPos.y);
    // Undecorate the window and resize it to the monitor.
    ChangeDecoration(true);
    glfwSetWindowPos(window_, monitorPos.x, monitorPos.y);
    // Maximize the window and set the stored dimensions of the window.
    glfwMaximizeWindow(window_);
    glfwGetWindowSize(window_, &data_.width_, &data_.height_);
  }

  void WindowManager::Focus()
  {
    glfwFocusWindow(window_);
  }

  void WindowManager::Resize(int width, int height)
  {
    data_.width_ = width;
    data_.height_ = height;
    glfwSetWindowSize(window_, width, height);
  }

  void WindowManager::ChangeDecoration(bool decorated)
  {
    data_.decorated_ = decorated;
    glfwSetWindowAttrib(window_, GLFW_DECORATED, decorated);
  }

  void WindowManager::ChangeTitle(const std::string& title)
  {
    data_.title_ = title;
    glfwSetWindowTitle(window_, title.c_str());
  }

  void WindowManager::Change(const WindowData& data)
  {
    Resize(data.width_, data.height_);
    ChangeDecoration(data.decorated_);
    ChangeTitle(data.title_);
  }

  void WindowManager::RecreateOsWindow(const WindowData& settings)
  {
    // Delete the window, if we got it.
    if (window_)
    {
      glfwDestroyWindow(window_);
      window_ = nullptr;
    }
    // Then create the window according to the specifications.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(settings.width_, settings.height_, settings.title_.c_str(), nullptr, nullptr);
    if (!window_)
    {
      throw std::runtime_error("Failed to create the window with the given settings.");
    }
    // Update the internal variables.
    Change(settings);
    // Set the user pointer.
    glfwSetWindowUserPointer(window_, this);
  }

  bool WindowManager::IsFocused() const
  {
    return glfwGetWindowAttrib(window_, GLFW_FOCUSED);
  }

  const WindowManager::WindowData& WindowManager::GetSettings() const
  {
    return data_;
  }

  GLFWwindow* WindowManager::GetInternalHandle()
  {
    return window_;
  }

  const GLFWwindow* WindowManager::GetInternalHandle() const
  {
    return window_;
  }

  const GLFWmonitor* WindowManager::GetParentMonitor() const
  {
    // Get the monitors the user has plugged in.
    int count = 0;
    GLFWmonitor** monitors = nullptr;
    monitors = glfwGetMonitors(&count);
    // Get the position of the monitor.
    glm::ivec2 position;
    glfwGetWindowPos(window_, &position.x, &position.y);
    // Get the position of all the monitors to the users.
    for (int i = 0; i < count; ++i)
    {
      // Get the size and position of the monitor.
      glm::ivec2 monitorPos, monitorSize;
      glfwGetMonitorWorkarea(monitors[i], &monitorPos.x, &monitorPos.y, &monitorSize.x, &monitorSize.y);
      // Check if the position of the window fits within the bounds of the window.
      if (position.x < monitorPos.x || position.y < monitorPos.y)
      {
        continue;
      }
      if (position.x > monitorPos.x + monitorSize.x || position.y > monitorPos.y + monitorSize.y)
      {
        continue;
      }
      // After making it through the check we found the one we want.
      // The window can only be in one monitor at a time.
      return monitors[i];
    }

    return glfwGetPrimaryMonitor();
  }

  GLFWmonitor* WindowManager::GetParentMonitor()
  {
    // Get the monitors the user has plugged in.
    int count = 0;
    GLFWmonitor** monitors = nullptr;
    monitors = glfwGetMonitors(&count);
    // Get the position of the monitor.
    glm::ivec2 position;
    glfwGetWindowPos(window_, &position.x, &position.y);
    // Get the position of all the monitors to the users.
    for (int i = 0; i < count; ++i)
    {
      // Get the size and position of the monitor.
      glm::ivec2 monitorPos, monitorSize;
      glfwGetMonitorWorkarea(monitors[i], &monitorPos.x, &monitorPos.y, &monitorSize.x, &monitorSize.y);
      // Check if the position of the window fits within the bounds of the window.
      if (position.x < monitorPos.x || position.y < monitorPos.y)
      {
        continue;
      }
      if (position.x > monitorPos.x + monitorSize.x || position.y > monitorPos.y + monitorSize.y)
      {
        continue;
      }
      // After making it through the check we found the one we want.
      // The window can only be in one monitor at a time.
      return monitors[i];
    }

    return glfwGetPrimaryMonitor();
  }
}
