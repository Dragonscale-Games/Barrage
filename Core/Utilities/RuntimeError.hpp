/* ========================================================================= */
/*!
 *
 * \file            RuntimeError.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used for when Barrage code throws an exception.
 * We should never catch exceptions thrown by the standard as that
 * makes debugging code waaay harder than it needs to be--that's from
 * experience.
 */
 /* ========================================================================= */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef RuntimeError_MODULE_H
#define RuntimeError_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <stdexcept>

namespace Barrage
{
  //! This might as well be a runtime error but it creates a layer of
  //! separation between the standard library and Barrage.
  class RuntimeError : public std::runtime_error
  {
  };
}

#endif // RuntimeError_MODULE_H
