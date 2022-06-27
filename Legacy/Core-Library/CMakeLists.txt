# =============================================================================
# File:             CMakeLists.txt
# Author:           David Wong Cascante
# Email:            david.wongcascante@digipen.edu
# Project:          Barrage Engine
# Date:             4/26/2021
# =============================================================================

# =============================================================================
# Set up any initial independent variables
# =============================================================================

# Set a macro for the variable name.
set(CORE_LIB_NAME "Barrage-Core")

# =============================================================================
# Set up the sources for this directory.
# =============================================================================

# Includes the project directory for the core project.

# All the source files go here, please add the sources through Visual Studio.
add_library(${CORE_LIB_NAME} STATIC
  "Source/stdafx.h"
  "Source/Random/Random.cpp"  "Source/Random/Random.hpp" 
  "Source/Engine/Engine.cpp" "Source/Engine/Engine.hpp"    
  "Source/GameStates/GameStateManager.cpp" "Source/GameStates/GameStateManager.hpp" 
  "Source/GameStates/GameState.cpp" "Source/GameStates/GameState.hpp" 
  "Source/Utilities/Utilities.hpp" 
  
  "Source/Rendering/WindowManager.hpp" "Source/Rendering/WindowManager.cpp"
  "Source/TempRenderer/TestRenderer.cpp" "Source/TempRenderer/TestRenderer.hpp" 
  "Source/TempRenderer/TempShader/TestShader.cpp" "Source/TempRenderer/TempShader/TestShader.hpp" 
  "Source/TempRenderer/TempShader/TestShaderManager.cpp" "Source/TempRenderer/TempShader/TestShaderManager.hpp" 
  "Source/TempRenderer/TempTexture/TestTexture.cpp" "Source/TempRenderer/TempTexture/TestTexture.hpp" 
  "Source/TempRenderer/TempTexture/TestTextureManager.cpp" "Source/TempRenderer/TempTexture/TestTextureManager.hpp" 
  "Source/Input/InputManager.cpp" "Source/Input/InputManager.hpp" 
  "Source/Input/KeyMap.hpp" 
  "Source/Rendering/GfxManager2D.hpp"  "Source/Rendering/GfxManager2D.cpp" 
  "Source/Rendering/GfxRenderer2D.hpp" "Source/Rendering/GfxRenderer2D.cpp" 
  "Source/Rendering/GfxDraw2D.hpp" 

  "Source/Objects/Components/BaseClasses/ObjectComponent.cpp" "Source/Objects/Components/BaseClasses/ObjectComponent.hpp" 
  "Source/Objects/Components/BaseClasses/PoolComponent.cpp"   "Source/Objects/Components/BaseClasses/PoolComponent.hpp"   
  "Source/Objects/Components/BaseClasses/BaseComponent.hpp" 
  "Source/Objects/ObjectManager.cpp" "Source/Objects/ObjectManager.hpp" 
  "Source/Objects/Pools/Pool.cpp"    "Source/Objects/Pools/Pool.hpp"     

  "Source/Objects/Systems/EngineSystems.hpp"
  "Source/Objects/Systems/BaseSystem.cpp"                    "Source/Objects/Systems/BaseSystem.hpp"   
  "Source/Objects/Systems/Destruction/DestructionSystem.cpp" "Source/Objects/Systems/Destruction/DestructionSystem.hpp"    
  "Source/Objects/Systems/Creation/CreationSystem.cpp"       "Source/Objects/Systems/Creation/CreationSystem.hpp"  
  "Source/Objects/Systems/Draw/DrawSystem.cpp"               "Source/Objects/Systems/Draw/DrawSystem.hpp" 

  "Source/Objects/Components/EngineComponents.hpp"
  "Source/Objects/Components/ObjectComponents/Destructible/Destructible.hpp" 
  "Source/Objects/Components/ObjectComponents/Position/Position.hpp" 
  "Source/Objects/Components/ObjectComponents/Rotation/Rotation.hpp" 
  "Source/Objects/Components/ObjectComponents/Scale/Scale.hpp" 
  "Source/Objects/Components/PoolComponents/Spawner/Spawner.cpp" "Source/Objects/Components/PoolComponents/Spawner/Spawner.hpp" 
  "Source/Objects/Components/PoolComponents/Sprite/Sprite.cpp"   "Source/Objects/Components/PoolComponents/Sprite/Sprite.hpp" 
  "Source/Objects/Components/PoolComponents/Tags/Tags.cpp"       "Source/Objects/Components/PoolComponents/Tags/Tags.hpp"  

  "Source/Objects/Initializers/EngineInitializers.hpp" 

  "Source/Objects/Initializers/InitializerManager.hpp" "Source/Objects/Initializers/InitializerManager.cpp"  
  "Source/Rendering/GfxFactory2D.hpp" 
  "Source/Objects/Archetypes/ArchetypeManager.cpp"                "Source/Objects/Archetypes/ArchetypeManager.hpp" 
  "Source/Objects/Pools/PoolManager.cpp"                          "Source/Objects/Pools/PoolManager.hpp" 
  "Source/Objects/Systems/SystemManager.cpp"                      "Source/Objects/Systems/SystemManager.hpp" 
  "Source/Objects/Components/ComponentAllocator.cpp"              "Source/Objects/Components/ComponentAllocator.hpp" 
  "Source/Objects/Archetypes/ObjectArchetype/ObjectArchetype.hpp" "Source/Objects/Archetypes/ObjectArchetype/ObjectArchetype.cpp" 
  "Source/Objects/Archetypes/PoolArchetype/PoolArchetype.hpp"     "Source/Objects/Archetypes/PoolArchetype/PoolArchetype.cpp" 
  
  "Source/Spaces/Space.cpp" "Source/Spaces/Space.hpp" 
  "Source/Spaces/SpaceManager.cpp" "Source/Spaces/SpaceManager.hpp"  
  
  "Source/Serialization/Reflection.hpp" "Source/Serialization/Reflection.cpp"   
  "Source/GLError.hpp" 
     
  "Source/Scenes/SceneManager.hpp" "Source/Scenes/SceneManager.cpp" 
  "Source/Scenes/Scene.hpp" "Source/Scenes/Scene.cpp"     "Source/Serialization/Parser.hpp" "Source/Serialization/Parser.cpp")


# =============================================================================
# Include the library headers.
# =============================================================================

# Link the include directories.
include_directories(${LIB_INCLUDES})
message("RapidJSON include: " ${RAPIDJSON_INCLUDE_DIR})
include_directories(${RAPIDJSON_INCLUDE_DIR})
# Put included source files here.
target_include_directories(${CORE_LIB_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_link_libraries(${CORE_LIB_NAME} glfw glad stb_image glm)
