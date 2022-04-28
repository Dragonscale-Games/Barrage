/* ======================================================================== */
/*!
 * \file            TestTexture.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary texture class to make it convenient to test game systems.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TestTexture_BARRAGE_H
#define TestTexture_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  //! Temporary texture class to make it convenient to test game systems.
  class TestTexture
  {
  public:
    TestTexture(unsigned textureID);

    ~TestTexture();

    unsigned GetID() const;

  private:
    unsigned textureID_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TestTexture_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////