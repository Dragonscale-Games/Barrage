/* ======================================================================== */
/*!
 * \file            MiscellaneousRules.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Miscellaneous spawn rules that don't fit clearly anywhere else.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef MiscellaneousRules_BARRAGE_H
#define MiscellaneousRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <Objects/Spawning/SpawnRule.hpp>
#include "ComponentArrays/PositionArray.hpp"
#include "ComponentArrays/VelocityArray.hpp"
#include <glm/glm.hpp>
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  namespace Spawn
  {
    struct SpawnRingData
    {
      unsigned numObjects_;
      float radius_;

      inline SpawnRingData() : numObjects_(10), radius_(100.0f) {};
    };
    
    class SpawnRing : public SpawnRuleT<SpawnRingData>
    {
      public:
        SpawnRing();
        
        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;

      private:
        static void SetPositionAndVelocity(Position& position, Velocity& velocity, const Position& origin, float theta, float speed, float radius);
    };

    struct MirrorAcrossAxisData
    {
      glm::mat2 rotationMatrix_;
      
      RADIAN angle_;

      inline MirrorAcrossAxisData() : rotationMatrix_(1.0f), angle_(0.0f) {};
    };

    class MirrorAcrossAxis : public SpawnRuleT<MirrorAcrossAxisData>
    {
      public:
        MirrorAcrossAxis();

        void Execute(Barrage::Pool& initPool, Barrage::Pool& destPool, unsigned firstObjIndex, unsigned numNewObjects, std::vector<unsigned>& sourceIndices) override;

        void SetRTTRValue(const rttr::variant& value);
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // MiscellaneousRules_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////