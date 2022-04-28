/* ======================================================================== */
/*!
 * \file            STUB.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef STUB_BARRAGE_H
#define STUB_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/SharedComponent.hpp"

namespace Barrage
{
  //! Holds all information needed to draw the objects in a pool
  class Sprite : public SharedComponent
  {
    public:
      std::string texture_; //!< Name of the texture to draw with
      unsigned layer_;      //!< Layer of the drawn object (lower layers are drawn beneath higher ones)

      inline Sprite() : texture_(), layer_(0) {}
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // STUB_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////