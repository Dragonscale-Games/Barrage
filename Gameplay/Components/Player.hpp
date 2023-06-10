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

#include "Objects/Components/BaseClasses/Component.hpp"

#include <unordered_map>
#include <string>

namespace Barrage
{
  //! Basic player component
  class Player
  {
    public:
      float speedSlow_;
      float speedFast_;
      
      inline Player() : speedSlow_(3.5f), speedFast_(7.0f) {}
  };

  typedef Barrage::ComponentT<Player> PlayerComponent;
}

////////////////////////////////////////////////////////////////////////////////
#endif // Player_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////