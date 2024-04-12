/* ======================================================================== */
/*!
 * \file            InputManager.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
 * A description goes here..? <- Sorry to modify this -David

 */
/* ======================================================================== */

#include "stdafx.h"
#include "InputManager.hpp"

namespace Barrage
{
  InputManager::InputManager() :
    window_(nullptr),
    keyTriggers_(MAX_KEY_VALUE - MIN_KEY_VALUE + 1, 0),
    keyReleases_(MAX_KEY_VALUE - MIN_KEY_VALUE + 1, 0)
  {
  }

  void InputManager::Initialize(GLFWwindow* window)
  {
    if (!window_ && window)
    {
      window_ = window;
      glfwSetWindowUserPointer(window_, this);
      glfwSetKeyCallback(window_, KeyCallback);
    }
  }

  void InputManager::Reset()
  {
    std::fill(keyTriggers_.begin(), keyTriggers_.end(), false);
    std::fill(keyReleases_.begin(), keyReleases_.end(), false);
  }

  void InputManager::Shutdown()
  {
    // if the input manager is currently running...
    if (window_)
    {
      glfwSetKeyCallback(window_, nullptr);
      glfwSetWindowUserPointer(window_, nullptr);
      window_ = nullptr;
    }
  }

  bool InputManager::KeyTriggered(int key) const
  {
    if (!KeyIsValid(key))
    {
      return 0;
    }
    
    return keyTriggers_[static_cast<long long>(key - MIN_KEY_VALUE)];
  }

  bool InputManager::KeyIsDown(int key) const
  {
    if (!KeyIsValid(key))
    {
      return false;
    }

    return glfwGetKey(window_, key) == GLFW_PRESS;
  }

  bool InputManager::KeyReleased(int key) const
  {
    if (!KeyIsValid(key))
    {
      return 0;
    }
    
    return keyReleases_[static_cast<long long>(key - MIN_KEY_VALUE)];
  }

  bool InputManager::KeyIsValid(int key)
  {
    return key >= MIN_KEY_VALUE && key <= MAX_KEY_VALUE;
  }

  void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    UNREFERENCED(window);
    UNREFERENCED(scancode);
    UNREFERENCED(mods);

    InputManager* manager = reinterpret_cast<InputManager*>(glfwGetWindowUserPointer(window));

    if (!KeyIsValid(key) || manager == nullptr)
    {
      return;
    }

    switch (action)
    {
      case GLFW_PRESS:
        manager->keyTriggers_[static_cast<long long>(key - MIN_KEY_VALUE)] = true;
        break;

      case GLFW_RELEASE:
        manager->keyReleases_[static_cast<long long>(key - MIN_KEY_VALUE)] = true;
        break;
    }
  }
}