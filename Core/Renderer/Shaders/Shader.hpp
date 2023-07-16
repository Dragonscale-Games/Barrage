/* ======================================================================== */
/*!
 * \file            Shader.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Shader class for simple renderer.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Shader_BARRAGE_H
#define Shader_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  //! Shader class for simple renderer
  class Shader
  {
  public:
    Shader(unsigned programID);

    ~Shader();

    unsigned GetID() const;

  private:
    unsigned programID_;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Shader_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////