/* ======================================================================== */
/*!
 * \file            TestShader.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Temporary shader class to make it convenient to test game systems.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TestShader_BARRAGE_H
#define TestShader_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  //! Temporary shader class to make it convenient to test game systems.
  class TestShader
  {
  public:
    TestShader(unsigned programID);

    ~TestShader();

    unsigned GetID() const;

  private:
    unsigned programID_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TestShader_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////