/* ======================================================================== */
/*!
 * \file            Texture.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Texture class for simple renderer.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Texture_BARRAGE_H
#define Texture_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  //! Texture class for simple renderer
  class Texture
  {
  public:
    Texture(unsigned textureID);

    ~Texture();

    unsigned GetID() const;

  private:
    unsigned textureID_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Texture_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////