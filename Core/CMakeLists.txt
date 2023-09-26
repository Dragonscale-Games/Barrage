# =====================================================================================================================
# MIT License
# 
# Copyright (c) 2022 Dragonscale-Games
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# =====================================================================================================================


# =====================================================================================================================
# File:         CMakeLists.txt
# Author:       David Wong Cascante
# Email:        dragonscale.games.llc@gmail.com
# Date:         1/8/2022
# =====================================================================================================================

# Sets the folder name for OS specific implementations.
if(MSVC)
  set(OS_IMPL_FOLDER "MSVC")
else()
  set(OS_IMPL_FOLDER "LINUX")
endif()

# Add the sources for the core library.
add_library(BarrageCore STATIC 
  "Engine.cpp" 

  "Actions/ActionManager.cpp" 

  "Audio/AudioManager.cpp"

  "Entry/Entry.cpp"  

  "Framerate/FramerateController.cpp"

  "Input/InputManager.cpp"

  "Logger/Logger.cpp" 

  "Objects/Archetypes/ObjectArchetype.cpp" 
  "Objects/Archetypes/PoolArchetype.cpp" 
  "Objects/Components/ComponentFactory.cpp"
  "Objects/Pools/Pool.cpp" 
  "Objects/Spawning/SpawnRule.cpp" 
  "Objects/Systems/System.cpp" 
  "Objects/Systems/SystemManager.cpp" 

  "Random/Random.cpp"

  "Renderer/Framebuffers/Framebuffer.cpp"
  "Renderer/Shaders/Shader.cpp" 
  "Renderer/Textures/Texture.cpp" 
  "Renderer/Textures/TextureManager.cpp" 
  "Renderer/Renderer.cpp" 

  "Scenes/Scene.cpp" 
  "Scenes/SceneManager.cpp" 

  "Serialization/Serializer.cpp"

  "Spaces/Space.cpp" 
  "Spaces/SpaceManager.cpp" 

  "Window/WindowManager.cpp"
   "Registration/Registrar.cpp" "Memory/MemoryDebugger.cpp" "Objects/Components/Component.cpp" "Objects/Components/ComponentArray.cpp")

# And link the dependencies for this library.
# target_link_libraries(BarrageCore PUBLIC glad glfw glm rapidjson stb_image RTTR::Core)
target_link_libraries(BarrageCore LINK_PUBLIC spdlog::spdlog glad glfw glm rapidjson stb_image RTTR::Core Soloud)
if(WIN32)
  target_link_libraries(BarrageCore PUBLIC DbgHelp Userenv)
endif()
target_include_directories(BarrageCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/ThirdParty/soloud/include")