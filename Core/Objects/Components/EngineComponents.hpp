/* ======================================================================== */
/*!
 * \file            EngineComponents.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Definitions of each component that's built into the engine.
 */
/* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef EngineComponents_BARRAGE_H
#define EngineComponents_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "ComponentArrays/AngularSpeedArray.hpp"
#include "ComponentArrays/DestructibleArray.hpp"
#include "ComponentArrays/DirectoryIndexArray.hpp"
#include "ComponentArrays/LifetimeArray.hpp"
#include "ComponentArrays/Transform/PositionArray.hpp"
#include "ComponentArrays/Transform/RotationArray.hpp"
#include "ComponentArrays/Transform/ScaleArray.hpp"
#include "ComponentArrays/VelocityArray.hpp"

#include "SharedComponents/BoundaryBox.hpp"
#include "SharedComponents/CircleCollider.hpp"
#include "SharedComponents/ObjectDirectory.hpp"
#include "SharedComponents/Player.hpp"
#include "SharedComponents/RNG.hpp"
#include "SharedComponents/Spawner.hpp"
#include "SharedComponents/Sprite.hpp"

////////////////////////////////////////////////////////////////////////////////
#endif // EngineComponents_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////