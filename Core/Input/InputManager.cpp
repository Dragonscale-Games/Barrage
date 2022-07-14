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

//#include <glad/gl.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>

namespace Barrage
{
  InputManager* InputManager::manager_ = nullptr;

  InputManager::InputManager() :
    window_(nullptr),
    keysPrev_(),
    keysCurr_(),
    keysBuff_()
  {
  }

  void InputManager::Initialize(GLFWwindow* window)
  {
    // if the input manager isn't initialized and the input window is valid...
    if (!window_ && window)
    {
      // correctly size vectors and fill them with false
      keysPrev_.assign(MAX_KEY_VALUE + 2, false);
      keysCurr_.assign(MAX_KEY_VALUE + 2, false);
      keysBuff_.assign(MAX_KEY_VALUE + 2, false);
      
      window_ = window;
      manager_ = this;
      glfwSetKeyCallback(window, KeyCallback);
    }
  }

  void InputManager::Update()
  {
    glfwPollEvents();
    
    keysPrev_ = keysCurr_;
    keysCurr_ = keysBuff_;
  }

  void InputManager::Shutdown()
  {
    // if the input manager is currently running...
    if (window_)
    {
      glfwSetKeyCallback(window_, nullptr);
      manager_ = nullptr;
      window_ = nullptr;
    }
  }

  bool InputManager::KeyTriggered(KEY key) const
  {
    return keysCurr_[static_cast<long long>(key) + 1] && !keysPrev_[static_cast<long long>(key) + 1];
  }

  bool InputManager::KeyIsDown(KEY key) const
  {
    return keysCurr_[static_cast<long long>(key) + 1];
  }

  bool InputManager::KeyReleased(KEY key) const
  {
    return !keysCurr_[static_cast<long long>(key) + 1] && keysPrev_[static_cast<long long>(key) + 1];
  }

  void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    UNREFERENCED(window);
    UNREFERENCED(scancode);
    UNREFERENCED(mods);

    switch (action)
    {
      case GLFW_PRESS:
        manager_->keysBuff_[static_cast<long long>(key) + 1] = true;
        break;

      case GLFW_RELEASE:
        manager_->keysBuff_[static_cast<long long>(key) + 1] = false;
        break;
    }
  }
}