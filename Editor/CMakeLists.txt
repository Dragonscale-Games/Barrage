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

set(BARRAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(Editor "Source/main.cpp" 
"Source/GUI/GUI.cpp" 
"Source/Editor/Editor.cpp"
"${BARRAGE_SOURCE_DIR}/Samples/DemoGame/Source/Registration.cpp"
"../Samples/DemoGame/Source/Systems/Collision/CollisionSystem.cpp"
"../Samples/DemoGame/Source/Systems/Movement/MovementSystem.cpp"
"../Samples/DemoGame/Source/Systems/Spawn/SpawnSystem.cpp"
"${BARRAGE_SOURCE_DIR}/Samples/DemoGame/Source/Initialization/DemoInitialization.cpp" 
"../Samples/DemoGame/Source/SpawnFuncs/Direction/DirectionFuncs.cpp"
"../Samples/DemoGame/Source/SpawnFuncs/Position/PositionFuncs.cpp"
"Source/Widgets/Windows/Hierarchy/HierarchyWidget.cpp"
"Source/Widgets/Windows/Inspector/InspectorWidget.cpp"

"Source/Editor/EditorData.cpp"
 "Source/Widgets/MainMenu/MainMenuWidget.cpp" 
 "Source/Widgets/Component/ComponentWidget.cpp"  
 "Source/Widgets/Data/DataWidget.cpp" 
 "Source/Widgets/Windows/Log/LogWidget.cpp"  
 "Source/Commands/Command.cpp" 
 "Source/Commands/CommandQueue.cpp" 
 "Source/Commands/ChangeValue/ChangeValue.cpp" 
 "Source/Commands/Create/Pool/CreatePool.cpp" 
 "Source/Commands/Create/Object/CreateObject.cpp" 
 "Source/Widgets/Popups/Object/ObjectPopupWidget.cpp" 
 "Source/Widgets/Popups/Pool/PoolPopupWidget.cpp" 
 "Source/Widgets/Popups/Scene/ScenePopupWidget.cpp" 
 "Source/Commands/Delete/Object/DeleteObject.cpp" 
 "Source/Commands/Delete/Pool/DeletePool.cpp")

target_link_libraries(Editor PUBLIC BarrageCore imgui)
target_include_directories(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(Editor PUBLIC "${BARRAGE_SOURCE_DIR}/Core")
target_include_directories(Editor PUBLIC "${BARRAGE_SOURCE_DIR}/Samples/DemoGame/Source/Initialization")
target_include_directories(Editor PUBLIC "${BARRAGE_SOURCE_DIR}/Samples/DemoGame")
file(COPY "${BARRAGE_SOURCE_DIR}/Samples/DemoGame/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
