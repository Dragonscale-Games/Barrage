/* ======================================================================== */
/*!
 * \file            GLError.hpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * All common code for checking OpenGL errors.
 */
/* ======================================================================== */

#ifndef GL_Error_HPP
#define GL_Error_HPP

#include <cassert>
#include <glad/gl.h>

/****************************************************************************/
/*!
  \brief
    Checks if an OpenGL call released an error caught by OpenGL.
  \param X
    The OpenGL expression to execute before checking for errors.
*/
/****************************************************************************/
#if !defined(_OPTIMIZED_) 
#define CHECK_GL(X) X; assert(glGetError() == GL_NO_ERROR)
#else
#define CHECK_GL(X) X
#endif

#endif // GL_Error_HPP

