/* ======================================================================== */
/*!
 * \file            EngineComponents.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Definitions of each component that's built into the engine.
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef EngineComponents_BARRAGE_H
#define EngineComponents_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseClasses/ComponentArray.hpp"
#include "BaseClasses/SharedComponent.hpp"
#include "Utilities/Utilities.hpp"
#include "Objects/SpawnFuncs/SpawnFuncManager.hpp"

#include <unordered_set>
#include <string>

namespace Barrage
{
  // ===================================================================
  // Component Arrays
  // ===================================================================
  
  //!< World position of an object
  struct Position
  {
    float x_; //!< x coord in world units
    float y_; //!< y coord in world units

    inline Position() : x_(0.0f), y_(0.0f) {}
  };
  typedef ComponentArrayT<Position> PositionArray;

  //!< Counterclockwise rotation of an object
  struct Rotation
  {
    RADIAN angle_; //!< Rotation angle in radians

    inline Rotation() : angle_(0.0f) {}
  };
  typedef ComponentArrayT<Rotation> RotationArray;

  //!< World scale of an object
  struct Scale
  {
    float w_; //!< width in world units
    float h_; //!< height in world units

    inline Scale() : w_(100.0f), h_(100.0f) {}
  };
  typedef ComponentArrayT<Scale> ScaleArray;
  
  //!< Keeps track of whether an object is marked for destruction
  struct Destructible
  {
    bool destroyed_; //!< true if marked for destruction
    
    inline Destructible() : destroyed_(false) {}
  };
  typedef ComponentArrayT<Destructible> DestructibleArray;

  // ===================================================================
  // Shared Components
  // ===================================================================

  //! Component that allows objects to spawn other objects
  class Spawner : public SharedComponent
  {
    public:
      //!< Holds all information needed to spawn an object from another object
      struct SpawnType
      {
        std::vector<SpawnFunc> spawnFuncs_; //!< List of spawn functions to apply
        std::string poolName_;              //!< Name of pool the new object will spawn in
        std::string archetypeName_;         //!< Name of object archetype that will be cloned
        unsigned spawnNum_;                 //!< Number of objects to spawn this frame
      };

      std::vector<SpawnType> spawnTypes_; //!< List of the object types that will be spawned
    
      inline Spawner() : spawnTypes_() {}
  };

  //! Holds all information needed to draw the objects in a pool
  class Sprite : public SharedComponent
  {
    public:
      std::string texture_; //!< Name of the texture to draw with
      unsigned layer_;      //!< Layer of the drawn object (lower layers are drawn beneath higher ones)

      inline Sprite() : texture_(), layer_(0) {}
  };

  //! All tags that apply to an object pool (for instance: "Player", "Bullet", "Targets Player")
  class Tags : public SharedComponent
  {
    public:
      typedef std::unordered_set<std::string> TagSet;
    
      TagSet tagSet_; //!< Set of tags for the pool

      inline Tags() : tagSet_() {}

      inline bool HasTag(const std::string& tag) const { return tagSet_.count(tag); }
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // EngineComponents_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////