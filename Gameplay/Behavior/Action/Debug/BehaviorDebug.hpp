/* ======================================================================== */
/*!
 * \file            BehaviorDebug.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorDebug_BARRAGE_H
#define BehaviorDebug_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Behavior/BehaviorNode.hpp"

namespace Barrage
{
  namespace Behavior
  {
    struct DebugData
    {
      std::string text_;
      bool succeeds_;

      inline DebugData() : text_(), succeeds_(true) {};
    };
    
    class Debug : public BehaviorNodeT<DebugData>
    {
      public:
        Debug();

        std::shared_ptr<BehaviorNode> Clone() const override;

        BehaviorState Execute(BehaviorNodeInfo& info) override;

        static void Reflect();
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorDebug_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////