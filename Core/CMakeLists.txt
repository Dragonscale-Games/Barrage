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
  "template.cxx"

  "Actions/ActionManager.cpp" "Scenes/SceneManager.cpp"

  "Debug/SymbolManager.cpp" "Debug/${OS_IMPL_FOLDER}/SymbolManager.cpp"
  "Debug/MemoryDebugger.cpp" "Debug/${OS_IMPL_FOLDER}/MemoryDebugger.cpp"

  "Engine/Engine.cpp" 
  
  "File/FileManager.cpp" "File/${OS_IMPL_FOLDER}/FileManager.cpp"
  "File/FileManager.tpp"
  
  "File/Objects/ObjectSource.cpp"
  
  "FramerateController/FramerateController.cpp" 
  
  "Input/InputManager.cpp"
 
  "Objects/ObjectManager.cpp"
  "Objects/Pools/Pool.cpp"    
  
  "Objects/Systems/BaseSystem.cpp"                             

  "Objects/Spawning/SpawnFunctionManager.cpp"  
         
  "Objects/Pools/PoolManager.cpp"                        
  "Objects/Systems/SystemManager.cpp"                   
  "Objects/Components/ComponentAllocator.cpp"              
  "Objects/Archetypes/ObjectArchetype/ObjectArchetype.cpp" 
  "Objects/Archetypes/PoolArchetype/PoolArchetype.cpp" 
  "Objects/Pools/PoolType.cpp"  
  "Math/Curves.tpp"

  "Random/Random.cpp"

  "Renderer/Renderer.cpp" 
  "Renderer/Textures/Texture.cpp" 
  "Renderer/Textures/TextureManager.cpp" 
  "Renderer/Shaders/Shader.cpp" 
  "Renderer/Shaders/ShaderManager.cpp"
  
  "Scenes/Scene.cpp"

  "Serialization/Serializer.cpp"

  "Spaces/Space.cpp"
  "Spaces/SpaceManager.cpp" 

  "Utilities/RuntimeError.cpp"
  "Utilities/RecursionTable.tpp"
  "Utilities/Logger.cpp"

  "Objects/Spawning/SpawnInfo.cpp"  

  "Entry/Entry.cpp" )

add_library(barragecore ALIAS BarrageCore)
# And link the dependencies for this library.
# target_link_libraries(BarrageCore PUBLIC glad glfw glm rapidjson stb_image RTTR::Core)
target_link_libraries(BarrageCore LINK_PUBLIC spdlog::spdlog glad glfw glm rapidjson stb_image RTTR::Core)
if(WIN32)
  target_link_libraries(BarrageCore PUBLIC DbgHelp Userenv)
endif()
target_include_directories(BarrageCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")