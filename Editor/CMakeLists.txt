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

add_executable(Editor "main.cpp" 
"GUI/GUI.cpp" 
"Editor.cpp"

 "Widgets/Windows/Hierarchy/HierarchyWidget.cpp"
 "Widgets/Windows/Inspector/InspectorWidget.cpp"

 "EditorData.cpp"
 "Widgets/MainMenu/MainMenuWidget.cpp" 
  
 "Widgets/Data/DataWidget.cpp" 
 "Widgets/Windows/Log/LogWidget.cpp"  
 "Commands/Command.cpp" 
 "Commands/CommandQueue.cpp" 
  
 "Commands/Create/Pool/CreatePool.cpp" 
 "Commands/Create/Object/CreateObject.cpp" 
 "Widgets/Popups/Object/ObjectPopupWidget.cpp" 
 "Widgets/Popups/Pool/PoolPopupWidget.cpp" 
 "Widgets/Popups/Scene/ScenePopupWidget.cpp" 
 "Commands/Delete/Object/DeleteObject.cpp" 
 "Commands/Delete/Pool/DeletePool.cpp" 
 "Commands/Create/ComponentArray/CreateComponentArray.cpp" 
 "Commands/Create/Component/CreateComponent.cpp" 
 "Commands/Delete/ComponentArray/DeleteComponentArray.cpp" 
 "Commands/Delete/Component/DeleteComponent.cpp" 
 "Widgets/Popups/Component/ComponentPopupWidget.cpp" 
 "Widgets/Popups/ComponentArray/ComponentArrayPopupWidget.cpp"  
 "Widgets/Modals/ComponentArray/ComponentArrayModal.cpp" 
 "Widgets/Modals/Component/ComponentModal.cpp" 
 "Widgets/Components/ComponentArray/ComponentArrayWidget.cpp" 
 "Widgets/Components/Component/ComponentWidget.cpp"  
 "Commands/Edit/ComponentArray/EditComponentArray.cpp" 
 "Commands/Edit/Component/EditComponent.cpp")

target_link_libraries(Editor PUBLIC BarrageCore Gameplay imgui nativefiledialog)
add_dependencies(Editor Game)
target_include_directories(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Editor PUBLIC "${BARRAGE_SOURCE_DIR}/Core")

add_custom_command(TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:Game>" "executable"
)
add_custom_command(TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "Assets"
)
