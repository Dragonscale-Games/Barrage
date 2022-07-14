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
# Author:       David Cruse
# Email:        dragonscale.games.llc@gmail.com
# Date:         5/5/2022
# =====================================================================================================================

add_executable(Editor "Source/main.cpp" 
"Source/GUI/GUI.cpp" "Source/GUI/GUI.hpp" 
"Source/Editor/Editor.cpp" "Source/Editor/Editor.hpp"
"${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/GameStates/GS_DemoGame.cpp" "${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/GameStates/GS_DemoGame.hpp" 
"${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/Registration.cpp"
"${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/Systems/SpawnSystem.cpp" "${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/Systems/SpawnSystem.hpp"
"${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/Archetypes/DemoArchetypes.cpp" "${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/Archetypes/DemoArchetypes.hpp"
)

target_link_libraries(Editor PUBLIC BarrageCore imgui::imgui)
target_include_directories(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(Editor PUBLIC "${CMAKE_SOURCE_DIR}/Core")
target_include_directories(Editor PUBLIC "${CMAKE_SOURCE_DIR}/Samples/DemoGame/Source/GameStates/")
target_include_directories(Editor PUBLIC "${CMAKE_SOURCE_DIR}/Samples/DemoGame")
file(COPY "${CMAKE_SOURCE_DIR}/Samples/DemoGame/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
