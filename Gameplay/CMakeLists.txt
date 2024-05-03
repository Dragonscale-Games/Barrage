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
	"Registration/Registration.cpp"

	"Behavior/Action/Debug/BehaviorDebug.cpp"
	"Behavior/Action/Direction/Rotate/BehaviorRotateDirection.cpp"
	"Behavior/Action/Wait/BehaviorWait.cpp" 

	"Behavior/Composite/Sequence/BehaviorSequence.cpp" 
	"Behavior/Composite/Selector/BehaviorSelector.cpp"

	"Behavior/Decorator/AlwaysSucceed/BehaviorAlwaysSucceed.cpp" 
	"Behavior/Decorator/AlwaysFail/BehaviorAlwaysFail.cpp" 
	"Behavior/Decorator/Invert/BehaviorInvert.cpp" 
	"Behavior/Decorator/LoopOnFailure/BehaviorLoopOnFailure.cpp" 
	"Behavior/Decorator/LoopOnSuccess/BehaviorLoopOnSuccess.cpp"
	"Behavior/Decorator/Repeat/BehaviorRepeat.cpp"

	"Behavior/Parallel/Selector/BehaviorParallelSelector.cpp" 
	"Behavior/Parallel/Sequence/BehaviorParallelSequence.cpp" 

    "ComponentArrays/AngularSpeed/AngularSpeedArray.cpp" 
	"ComponentArrays/ColorTint/ColorTintArray.cpp" 
	"ComponentArrays/Destructible/DestructibleArray.cpp" 
	"ComponentArrays/Lifetime/LifetimeArray.cpp"
	"ComponentArrays/Position/PositionArray.cpp" 
	"ComponentArrays/Rotation/RotationArray.cpp" 
	"ComponentArrays/Scale/ScaleArray.cpp" 
	"ComponentArrays/TextureUV/TextureUVArray.cpp" 
	"ComponentArrays/Velocity/VelocityArray.cpp" 

	"Components/Behavior/Behavior.cpp"
	"Components/BoundaryBox/BoundaryBox.cpp" 
	"Components/CircleCollider/CircleCollider.cpp" 
	"Components/Movement/Movement.cpp"
	"Components/Player/Player.cpp" 
	"Components/Spawner/Spawner.cpp" 
	"Components/Sprite/Sprite.cpp" 
    
	"SpawnRules/Color/Set/SpawnSetColor.cpp"

	"SpawnRules/Count/Iterate/SpawnIterateCount.cpp"

	"SpawnRules/Direction/Adjust/SpawnAdjustDirection.cpp"
	"SpawnRules/Direction/Iterate/SpawnIterateDirection.cpp"
	"SpawnRules/Direction/MatchSpawner/SpawnMatchSpawnerDirection.cpp"
	"SpawnRules/Direction/Random/SpawnRandomDirection.cpp" 
	"SpawnRules/Direction/Set/SpawnSetDirection.cpp"

	"SpawnRules/Miscellaneous/Fan/SpawnFan.cpp" 
	"SpawnRules/Miscellaneous/Mirror/SpawnMirror.cpp"
	"SpawnRules/Miscellaneous/Ring/SpawnRing.cpp" 

	"SpawnRules/Orientation/Adjust/SpawnAdjustOrientation.cpp"
	"SpawnRules/Orientation/Iterate/SpawnIterateOrientation.cpp"
	"SpawnRules/Orientation/MatchSpawner/SpawnMatchSpawnerOrientation.cpp"
	"SpawnRules/Orientation/Random/SpawnRandomOrientation.cpp"

	"SpawnRules/Position/Adjust/SpawnAdjustPosition.cpp" 
	"SpawnRules/Position/Iterate/SpawnIteratePosition.cpp"
	"SpawnRules/Position/MatchSpawner/SpawnMatchSpawnerPosition.cpp"
	"SpawnRules/Position/RandomBox/SpawnRandomPositionBox.cpp" 
	"SpawnRules/Position/Set/SpawnSetPosition.cpp"

	"SpawnRules/Rotation/Adjust/SpawnAdjustRotation.cpp"
	"SpawnRules/Rotation/Iterate/SpawnIterateRotation.cpp"
	"SpawnRules/Rotation/MatchDirection/SpawnRotationMatchDirection.cpp" 
	"SpawnRules/Rotation/Random/SpawnRandomRotation.cpp"
	"SpawnRules/Rotation/Set/SpawnSetRotation.cpp"

	"SpawnRules/Speed/Adjust/SpawnAdjustSpeed.cpp"
	"SpawnRules/Speed/Iterate/SpawnIterateSpeed.cpp"
	"SpawnRules/Speed/Random/SpawnRandomSpeed.cpp"
	"SpawnRules/Speed/Set/SpawnSetSpeed.cpp"

	"Systems/Behavior/BehaviorSystem.cpp"
	"Systems/Collision/CollisionSystem.cpp"
	
	"Systems/Destruction/DestructionSystem.cpp"
	"Systems/Draw/DrawSystem.cpp"
	"Systems/Lifetime/LifetimeSystem.cpp"
	"Systems/Movement/MovementSystem.cpp"
	"Systems/Spawn/SpawnSystem.cpp"      
  )

target_link_libraries(Gameplay PUBLIC BarrageCore)
target_include_directories(Gameplay PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Gameplay PUBLIC "${BARRAGE_SOURCE_DIR}/Core")