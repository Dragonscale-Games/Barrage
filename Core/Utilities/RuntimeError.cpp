/* ========================================================================= */
/*!
 *
 * \file            RuntimeError.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used for when Barrage code throws an exception.
 * We should never catch exceptions thrown by the standard as that
 * makes debugging code waaay harder than it needs to be--that's from
 * experience.
 */
 /* ========================================================================= */

//  ===========================================================================
// Includes
//  ===========================================================================
#include "RuntimeError.hpp"

namespace Barrage
{
  RuntimeError::RuntimeError(const std::string_view& errorMsg) : runtime_error(errorMsg.data())
  {
  }
}
