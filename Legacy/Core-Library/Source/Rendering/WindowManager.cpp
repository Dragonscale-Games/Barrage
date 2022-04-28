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
#include <stdafx.h>
#include <stdexcept>

#include "WindowManager.hpp"
#include <glm/vec2.hpp>

namespace Barrage
{
  // Initializing the static variables.
  WindowManager* WindowManager::instance_ = nullptr;

  WindowManager::WindowManager() :
      window_(nullptr), data_{1440, 720, false, "Barrage"}
  {
    // If the instance variable is not set yet... then...
    // we set it.
    if (!instance_)
    {
      instance_ = this;
    }
  }

  WindowManager::~WindowManager()
  {
    // Unset the instance variable if it points to
    // this object.
    if (instance_ == this)
    {
      instance_ = nullptr;
    }
  }

  WindowManager::WindowManager(const WindowManager& rhs) :
    window_(nullptr), data_(rhs.data_)
  {
    // If the window exists for the other windowing system
    // then we make one of our own here.
    if (rhs.window_)
    {
      MakeWindow(rhs.data_);
    }
  }

  WindowManager& WindowManager::operator=(const WindowManager& rhs)
  {
    // Set all the variables for the data.
    data_.width_ = rhs.data_.width_;
    data_.height_ = rhs.data_.height_;
    data_.title_ = rhs.data_.title_;
    data_.decorated_ = rhs.data_.decorated_;

    // If the window exists for 'rhs' then we have to make our own too.
    if (rhs.window_)
    {
      MakeWindow(data_);
    }

    return *this;
  }

  void WindowManager::Initialize(const WindowData& settings)
  {
    // Initialize GLFW
    if(!glfwInit())
    {
      throw std::runtime_error("ERROR: Failed to initialize GLFW somehow.");
    }

    MakeWindow(settings);
  }

  void WindowManager::Shutdown()
  {
    glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
  }

  WindowManager* WindowManager::Instance()
  {
    return instance_;
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
    const GLFWvidmode* modes = glfwGetVideoMode(monitor);
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

  void WindowManager::MakeWindow(const WindowData& settings)
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
