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

# Includes the project directory for the core project.
set(CORE_LIB_NAME "Barrage-Core")
set(GAME_LIB_NAME "Barrage-Game")

# =============================================================================
# Set up the sources for this directory and create the executable.
# =============================================================================

# Put included source files here.
add_library(${GAME_LIB_NAME} STATIC ${SOURCES}    "Source/GameStates/TestGameStates/GSWong.cpp" "Source/GameStates/TestGameStates/GSWong.hpp" 
                                                  "Source/GameStates/TestGameStates/GSCruse.cpp" "Source/GameStates/TestGameStates/GSCruse.hpp" 
                                                  "Source/GameStates/GSEntry.cpp" "Source/GameStates/GSEntry.hpp" 
                                                  "Source/GameStates/TestGameStates/GSBaldeon.cpp" "Source/GameStates/TestGameStates/GSBaldeon.hpp" 
                                                  "Source/GameStates/TestGameStates/Cruse/GSBulletTest.cpp" "Source/GameStates/TestGameStates/Cruse/GSBulletTest.hpp" 
                                                  "Source/GameStates/TestGameStates/Cruse/GSMetaballs.cpp" "Source/GameStates/TestGameStates/Cruse/GSMetaballs.hpp" 
                                                  "Source/GameStates/TestGameStates/Cruse/GSWaves.cpp" "Source/GameStates/TestGameStates/Cruse/GSWaves.hpp"

                                                  "Source/Objects/Systems/GameSystems.hpp" 
                                                  "Source/Objects/Systems/Collision/CollisionSystem.cpp" "Source/Objects/Systems/Collision/CollisionSystem.hpp" 
                                                  "Source/Objects/Systems/Movement/MovementSystem.cpp" "Source/Objects/Systems/Movement/MovementSystem.hpp" 
                                                  "Source/Objects/Systems/Timer/TimerSystem.cpp" "Source/Objects/Systems/Timer/TimerSystem.hpp" 
                                                  "Source/Objects/Systems/Waveforms/WaveformSystem.cpp" "Source/Objects/Systems/Waveforms/WaveformSystem.hpp" 

                                                  "Source/Objects/Components/GameComponents.hpp" 
                                                  "Source/Objects/Components/ObjectComponents/AngularSpeed/AngularSpeed.hpp" 
                                                  "Source/Objects/Components/ObjectComponents/Velocity/Velocity.hpp" 
                                                  "Source/Objects/Components/ObjectComponents/Colliders/CircleCollider/CircleCollider.hpp"
                                                  "Source/Objects/Components/PoolComponents/RNG/RNG.hpp" "Source/Objects/Components/PoolComponents/RNG/RNG.cpp" 
                                                  "Source/Objects/Components/PoolComponents/Timer/Timer.hpp" "Source/Objects/Components/PoolComponents/Timer/Timer.cpp"                                                   

                                                  "Source/Objects/Initializers/GameInitializers.hpp" 
                                                  "Source/Objects/Initializers/Misc/MiscInitializers.hpp" "Source/Objects/Initializers/Misc/MiscInitializers.cpp"

                                                   "Source/Objects/GameRegistration.cpp")
# Tell the game project it depends on the core project to link correctly.
add_dependencies(${GAME_LIB_NAME} ${CORE_LIB_NAME})
target_link_libraries(${GAME_LIB_NAME} ${CORE_LIB_NAME})
# Tell theh project where all the include files are.
message("RapidJSON include: " ${RAPIDJSON_INCLUDE_DIR})
include_directories(${RAPIDJSON_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/Includes")
target_include_directories(${GAME_LIB_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Core-Library/Source")
target_include_directories(${GAME_LIB_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")
