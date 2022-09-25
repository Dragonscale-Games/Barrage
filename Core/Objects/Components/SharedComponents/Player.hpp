/* ======================================================================== */
/*!
 * \file            Player.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Basic player component.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Player_BARRAGE_H
#define Player_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/SharedComponent.hpp"

#include <unordered_map>
#include <string>

namespace Barrage
{
  //! Basic player component
  class Player : public SharedComponent
  {
    public:
      float speedSlow_;
      float speedFast_;
      
      inline Player() : speedSlow_(3.5f), speedFast_(7.0f) {}

      inline std::string GetClassName() override { return "Player"; }
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Player_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////