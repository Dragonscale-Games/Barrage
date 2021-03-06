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
  "stdafx.h"
  "Random/Random.cpp" "Random/Random.hpp"
  "Engine/Engine.cpp" "Engine/Engine.hpp"

  "GameStates/GameStateManager.cpp" "GameStates/GameStateManager.hpp" 
  "GameStates/GameState.cpp" "GameStates/GameState.hpp" 

  "File/FileManager.hpp" "File/FileManager.cpp" "File/${OS_IMPL_FOLDER}/FileManager.cpp"
  "File/FileManager.tpp"

  "File/Graphics/ImageSource.hpp" "File/Graphics/ImageSource.cpp"

  "Utilities/Utilities.hpp" 
  "Utilities/Mallocator.hpp"
  "Utilities/RuntimeError.hpp"

  "Debug/SymbolManager.hpp" "Debug/SymbolManager.cpp" "Debug/${OS_IMPL_FOLDER}/SymbolManager.cpp"
  "Debug/MemoryDebugger.hpp" "Debug/MemoryDebugger.cpp" "Debug/${OS_IMPL_FOLDER}/MemoryDebugger.cpp"
  "Debug/MemoryOverrides.hpp"
  
  "TempRenderer/TestRenderer.cpp" "TempRenderer/TestRenderer.hpp" 
  "TempRenderer/TempShader/TestShader.cpp" "TempRenderer/TempShader/TestShader.hpp" 
  "TempRenderer/TempShader/TestShaderManager.cpp" "TempRenderer/TempShader/TestShaderManager.hpp" 
  "TempRenderer/TempTexture/TestTexture.cpp" "TempRenderer/TempTexture/TestTexture.hpp" 
  "TempRenderer/TempTexture/TestTextureManager.cpp" "TempRenderer/TempTexture/TestTextureManager.hpp" 
  "Input/InputManager.cpp" "Input/InputManager.hpp" 
  "Input/KeyMap.hpp" 
  
  "Objects/Components/BaseClasses/ComponentArray.cpp" "Objects/Components/BaseClasses/ComponentArray.hpp" 
  "Objects/Components/BaseClasses/SharedComponent.cpp"   "Objects/Components/BaseClasses/SharedComponent.hpp"   
  "Objects/Components/BaseClasses/BaseComponent.hpp" 
  "Objects/ObjectManager.cpp" "Objects/ObjectManager.hpp" 
  "Objects/Pools/Pool.cpp"    "Objects/Pools/Pool.hpp"  
  
  "Objects/Systems/EngineSystems.hpp"
  "Objects/Systems/BaseSystem.cpp"                    "Objects/Systems/BaseSystem.hpp"   
  "Objects/Systems/Destruction/DestructionSystem.cpp" "Objects/Systems/Destruction/DestructionSystem.hpp"    
  "Objects/Systems/Creation/CreationSystem.cpp"       "Objects/Systems/Creation/CreationSystem.hpp"  
  "Objects/Systems/Draw/DrawSystem.cpp"               "Objects/Systems/Draw/DrawSystem.hpp" 
  
  "Objects/Components/EngineComponents.hpp"
  
  "Objects/SpawnFuncs/SpawnFuncManager.hpp"                "Objects/SpawnFuncs/SpawnFuncManager.cpp"  
  "Objects/Archetypes/ArchetypeManager.cpp"                "Objects/Archetypes/ArchetypeManager.hpp" 
  "Objects/Pools/PoolManager.cpp"                          "Objects/Pools/PoolManager.hpp" 
  "Objects/Systems/SystemManager.cpp"                      "Objects/Systems/SystemManager.hpp" 
  "Objects/Components/ComponentAllocator.cpp"              "Objects/Components/ComponentAllocator.hpp" 
  "Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp" "Objects/Archetypes/ObjectArchetype/ObjectArchetype.cpp" 
  "Objects/Archetypes/PoolArchetype/PoolArchetype.hpp"     "Objects/Archetypes/PoolArchetype/PoolArchetype.cpp" 
  "Objects/SpawnFuncs/EngineSpawnFuncs.hpp" 
  "Objects/Pools/PoolType.cpp" "Objects/Pools/PoolType.hpp" 
  "Objects/Components/ComponentArrays/DestructibleArray.hpp" 
  "Objects/Components/ComponentArrays/PositionArray.hpp" 
  "Objects/Components/ComponentArrays/ScaleArray.hpp" 
  "Objects/Components/ComponentArrays/RotationArray.hpp" 
  "Objects/Components/SharedComponents/Spawner.hpp"
  "Objects/Components/SharedComponents/Sprite.hpp"
  "Objects/Components/ComponentArrays/LifetimeArray.hpp" 
  "Objects/Components/ComponentArrays/VelocityArray.hpp" 
  "Objects/Components/SharedComponents/CircleCollider.hpp" 
  "Objects/Components/ComponentArrays/AngularSpeedArray.hpp" 

  "Rendering/WindowManager.hpp" "Rendering/WindowManager.cpp"
  "Rendering/GfxManager2D.hpp" "Rendering/GfxManager2D.cpp"
  "Rendering/GfxRenderer2D.hpp" "Rendering/GfxRenderer2D.cpp"
  "Rendering/GfxTypes.hpp" "Rendering/GfxTypes.cpp"
  "Rendering/GfxPrimitives.hpp" "Rendering/GfxPrimitives.cpp"
  "Rendering/GfxDraw2D.hpp" "Rendering/GfxDraw2D.cpp"
  "Rendering/GfxFactory2D.hpp" "Rendering/GfxFactory2D.cpp"
  "Rendering/GfxRegistry2D.hpp" "Rendering/GfxRegistry2D.cpp"
  "Rendering/GLError.hpp"

  "Objects/Systems/Movement/MovementSystem.hpp" "Objects/Systems/Movement/MovementSystem.cpp"
  "Objects/Systems/Collision/CollisionSystem.hpp" "Objects/Systems/Collision/CollisionSystem.cpp" 
  "Objects/Components/SharedComponents/RNG.hpp" 
  "Objects/SpawnFuncs/Direction/DirectionFuncs.hpp" "Objects/SpawnFuncs/Direction/DirectionFuncs.cpp"
  "Objects/SpawnFuncs/Position/PositionFuncs.hpp" "Objects/SpawnFuncs/Position/PositionFuncs.cpp"
  "Objects/Components/SharedComponents/BoundaryBox.hpp"
)

add_library(barragecore ALIAS BarrageCore)
# And link the dependencies for this library.
# target_link_libraries(BarrageCore PUBLIC glad glfw glm rapidjson stb_image RTTR::Core)
target_link_libraries(BarrageCore LINK_PUBLIC glad glfw glm::glm rapidjson stb_image)
target_include_directories(BarrageCore PUBLIC ${RTTR_DIR})
if(WIN32)
  target_link_libraries(BarrageCore PUBLIC DbgHelp Userenv)
endif()
target_include_directories(BarrageCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
