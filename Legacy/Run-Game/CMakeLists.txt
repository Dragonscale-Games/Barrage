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

set(GAME_NAME "Run-Game")
set(GAME_LIB_NAME "Barrage-Game")
set(CORE_LIB_NAME "Barrage-Core")

# =============================================================================
# Set up the sources for this directory and create the executable.
# =============================================================================

# Creates an object to represent the executable.
# Add the sources to the add_executable here
add_executable(${GAME_NAME} "Source/Main.cpp" "Source/Game/Game.cpp" "Source/Game/Game.hpp")
add_dependencies(${GAME_NAME} ${CORE_LIB_NAME} ${GAME_LIB_NAME})
# Includes the project directory for the core project.
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/Includes")
target_include_directories(${GAME_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(${GAME_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Core-Library/Source")
target_include_directories(${GAME_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/Game-Library/Source")

# Set the directory for the library binary.
if(WIN32)
    # Link the library binaries.
    # set(LIBS ${LIBS} "${CMAKE_SOURCE_DIR}/Dependencies/Windows/fmod_vc.lib")
    # set(DLL_LIBS "${CMAKE_SOURCE_DIR}/Dependencies/Windows/fmod.dll")
else()
    # set(DLL_LIBS "${CMAKE_SOURCE_DIR}/Dependencies/Unix/libfmod.so")
endif()

# Get any common packages easy to find on both platforms.
find_package(OpenGL REQUIRED)
set(LIBS OpenGL::GL)

set(LIBS ${LIBS} glfw)

# Link core the libraries
target_link_libraries(${GAME_NAME} ${CORE_LIB_NAME} ${GAME_LIB_NAME})

# Copy the assets folder where the game gets built
file(COPY "${PROJECT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
if(WIN32)
  # Copy over the DLLs over
  file(COPY ${DLL_LIBS} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
else()
endif()
