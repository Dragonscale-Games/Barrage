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
# Date:         6/7/23
# =====================================================================================================================

add_library(Gameplay STATIC
	"Registration.cpp"
	
	"SpawnFunctions/Direction/DirectionFuncs.cpp"
	"SpawnFunctions/Position/PositionFuncs.cpp"
	
	"Systems/Collision/CollisionSystem.cpp"
	"Systems/Creation/CreationSystem.cpp"
	"Systems/Destruction/DestructionSystem.cpp"
	"Systems/Draw/DrawSystem.cpp"
	"Systems/Movement/MovementSystem.cpp"
	"Systems/Spawn/SpawnSystem.cpp"
)

target_link_libraries(Gameplay PUBLIC BarrageCore)
target_include_directories(Gameplay PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Gameplay PUBLIC "${BARRAGE_SOURCE_DIR}/Core")