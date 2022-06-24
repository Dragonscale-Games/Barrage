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
# Date:         1/4/2022
# =====================================================================================================================

cmake_minimum_required(VERSION 3.16)

find_package(rttr CONFIG REQUIRED Core)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
set(NEED_PULLING_DEPENDENCIES "${rttr_FOUND} ${glfw3_FOUND} ${glm_FOUND}")

# Use FetchContent to find the dependencies which were not found through
# CMake's default find_package.
include(FetchContent)
# Download RTTR
message(${NEED_PULLING_DEPENDENCIES})
if(NOT (${NEED_PULLING_DEPENDENCIES} STREQUAL ""))
  # Which is special because RTTR needs be reinstalled.
  if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    FetchContent_Declare(
      vcpkg
      GIT_REPOSITORY "https://github.com/microsoft/vcpkg.git"
      GIT_TAG "03ca9b59af1506a86840e3a3a01a092f3333a29b" # 2022-01-08
    )
    FetchContent_Populate(vcpkg)
    set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake")
    # Reinstall the dependencies we need.
    find_package(rttr CONFIG REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
  endif()
endif()

# Create the project.
project(Barrage)
# Add the subdirectories for third party libraries.
add_subdirectory(ThirdParty)

# Set the compiler flags before building our own code.
if(MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /std:c++17 /EHsc /wd4201") # /WX
else()
  set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17") # -Werror
endif()

# Add the subdirectories for building the Barrage libraries.
add_subdirectory(Core)
add_subdirectory(Tests)
add_subdirectory(Samples)
add_subdirectory(Editor)
