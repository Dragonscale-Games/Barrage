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

set(EDITOR_NAME "Barrage-Editor")
set(GAME_LIB_NAME "Barrage-Game")
set(CORE_LIB_NAME "Barrage-Core")

# =============================================================================
# Set up the sources for this directory.
# =============================================================================


# Add all sources here...
add_executable(${EDITOR_NAME} "Source/Main.cpp"   
                              "Source/GUI/GUI.cpp" "Source/GUI/GUI.hpp" 
                              "Source/Editor/Editor.cpp" "Source/Editor/Editor.hpp"  
                              "Source/Widgets/Components/GameComponents/GameComponentWidgets.hpp" 
                              "Source/Widgets/Components/EngineComponents/EngineComponentWidgets.hpp"   
                              "Source/Widgets/Components/ComponentWidgets.hpp" 
                              "Source/Widgets/Components/EngineComponents/ObjectComponents/Destructible/DestructibleWidget.hpp" "Source/Widgets/Components/EngineComponents/ObjectComponents/Destructible/DestructibleWidget.cpp" 
                              "Source/Widgets/Components/EngineComponents/ObjectComponents/Position/PositionWidget.hpp" "Source/Widgets/Components/EngineComponents/ObjectComponents/Position/PositionWidget.cpp" 
                              "Source/Widgets/Components/EngineComponents/ObjectComponents/Rotation/RotationWidget.hpp" "Source/Widgets/Components/EngineComponents/ObjectComponents/Rotation/RotationWidget.cpp" 
                              "Source/Widgets/Components/EngineComponents/ObjectComponents/Scale/ScaleWidget.hpp" "Source/Widgets/Components/EngineComponents/ObjectComponents/Scale/ScaleWidget.cpp" 
                              "Source/Widgets/Components/EngineComponents/PoolComponents/Spawner/SpawnerWidget.hpp" "Source/Widgets/Components/EngineComponents/PoolComponents/Spawner/SpawnerWidget.cpp" 
                              "Source/Widgets/Components/EngineComponents/PoolComponents/Sprite/SpriteWidget.hpp" "Source/Widgets/Components/EngineComponents/PoolComponents/Sprite/SpriteWidget.cpp" 
                              "Source/Widgets/Components/EngineComponents/PoolComponents/Tags/TagsWidget.hpp" "Source/Widgets/Components/EngineComponents/PoolComponents/Tags/TagsWidget.cpp"  
                              "Source/Widgets/Widget.hpp"   
                              "Source/Widgets/Components/ComponentWidget.hpp")

add_dependencies(${EDITOR_NAME} ${CORE_LIB_NAME} ${GAME_LIB_NAME})
# Includes the project directory for the core project.
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/Includes")
message("RapidJSON include: " ${RAPIDJSON_INCLUDE_DIR})
include_directories(${RAPIDJSON_INCLUDE_DIR})
# target_include_directories(${EDITOR_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/Dependencies/Includes")
target_include_directories(${EDITOR_NAME} PUBLIC    "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(${EDITOR_NAME} INTERFACE "${CMAKE_SOURCE_DIR}/Core-Library/Source")
target_include_directories(${EDITOR_NAME} INTERFACE "${CMAKE_SOURCE_DIR}/Game-Library/Source")

# Link the library binaries.
if(WIN32)
    # set(LIBS ${LIBS} "${CMAKE_SOURCE_DIR}/Dependencies/Windows/fmod_vc.lib")
    # set(DLL_LIBS "${CMAKE_SOURCE_DIR}/Dependencies/Windows/fmod.dll")
else()
    # set(DLL_LIBS "${CMAKE_SOURCE_DIR}/Dependencies/Unix/libfmod.so")
endif()

# Find common packages on both platforms.
find_package(OpenGL REQUIRED)
set(LIBS OpenGL::GL)

set(LIBS ${LIBS} glfw imgui)

# Link core the libraries
target_link_libraries(${EDITOR_NAME} ${CORE_LIB_NAME} ${GAME_LIB_NAME})
# Link the core libraries the game depends on.
target_link_libraries(${EDITOR_NAME} ${LIBS})

# Copy the assets folder where the game gets built
file(COPY "${PROJECT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
# Copy/Link the DLLs
if(WIN32)
  file(COPY ${DLL_LIBS} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
else()
  target_link_libraries(${EDITOR_NAME} ${DLL_LIBS})
endif()
