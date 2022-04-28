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

# Find vcpkg through fetch content.
include(FetchContent)
FetchContent_Declare(
  vcpkg
  GIT_REPOSITORY "https://github.com/microsoft/vcpkg.git"
  GIT_TAG "03ca9b59af1506a86840e3a3a01a092f3333a29b" # 2022-01-08
)
FetchContent_Declare(
  glfw3
  GIT_REPOSITORY "https://www.github.com/glfw/glfw"
  GIT_TAG "b716ff5b975b7cda1b35f8aceba8bcbb2f919fe8"
)
FetchContent_Declare(
  glm
  GIT_REPOSITORY "https://www.github.com/g-truc/glm"
  GIT_TAG "6ad79aae3eb5bf809c30bf1168171e9e55857e45"
)

# And unleash into into this project.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  FetchContent_Populate(vcpkg)
  set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake")
endif()

# Create the project.
project(Barrage)
# Add the subdirectories for third party libraries.
add_subdirectory(Thirdparty)
find_package(rttr CONFIG REQUIRED)
FetchContent_MakeAvailable(glfw3 glm)

# Set the compiler flags before building our own code.
if(MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /WX /std:c++17 /EHsc")
else()
  set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++17")
endif()

# Add the subdirectories for building the Barrage libraries.
add_subdirectory(Core)
add_subdirectory(Tests)
add_subdirectory(Samples)
