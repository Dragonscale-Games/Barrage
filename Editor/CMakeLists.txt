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

add_executable(Editor 
"main.cpp" 
"Editor.cpp" 

"Commands/Command.cpp" 
"Commands/CommandQueue.cpp" 

"Data/EditorData.cpp"

"GUI/GUI.cpp" 

"Widgets/Components/ComponentArrayWidget.cpp" 
"Widgets/Components/ComponentWidget.cpp"  

"Widgets/Data/DataWidget.cpp" 

"Widgets/MainMenu/MainMenuWidget.cpp"  

"Widgets/Modals/ComponentArray/ComponentArrayModal.cpp" 
"Widgets/Modals/Component/ComponentModal.cpp" 
"Widgets/Modals/Project/ProjectModal.cpp" 
"Widgets/Modals/Rename/RenameModal.cpp" 
"Widgets/Modals/SaveProject/SaveProjectModal.cpp"
"Widgets/Modals/Tag/TagModal.cpp"

"Widgets/Popups/Component/ComponentPopupWidget.cpp" 
 "Widgets/Popups/ComponentArray/ComponentArrayPopupWidget.cpp"  
"Widgets/Popups/Object/ObjectPopupWidget.cpp" 
"Widgets/Popups/Pool/PoolPopupWidget.cpp" 
"Widgets/Popups/Scene/ScenePopupWidget.cpp" 

"Widgets/Windows/Hierarchy/HierarchyWidget.cpp"
"Widgets/Windows/Inspector/InspectorWidget.cpp"
"Widgets/Windows/Log/LogWidget.cpp"  
"Widgets/Windows/Game/GameWidget.cpp"  
"Widgets/Windows/Timeline/TimelineWidget.cpp" 
"Widgets/Windows/Performance/PerformanceWidget.cpp"
)

target_link_libraries(Editor PUBLIC BarrageCore Gameplay imgui nativefiledialog)
add_dependencies(Editor Game)
target_include_directories(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Editor PUBLIC "${BARRAGE_SOURCE_DIR}/Core")

add_custom_command(TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:Game>" "executable"
)
