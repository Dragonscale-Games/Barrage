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

# Linux needs the vcpkg toolchain manually set; MSVC uses CMakeSettings.json
if(!MSVC)
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Create the project.
project(Barrage)

# Set the working directory as the root?
set(${WORKING_DIRECTORY} ${CMAKE_SOURCE_DIR})

# Add the subdirectories for third party libraries.
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(rapidjson REQUIRED)
find_package(rttr REQUIRED Core)
find_package(spdlog REQUIRED)
add_subdirectory(ThirdParty)

# Set the compiler flags before building our own code.
if(MSVC)
  set(CMAKE_CXX_FLAGS "/W4 /std:c++17 /EHsc /wd4201") # /WX
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17") # -Werror
endif()

# Add the subdirectories for building the Barrage libraries.
add_subdirectory(Core)
add_subdirectory(Game)
add_subdirectory(Samples)
add_subdirectory(Editor)
