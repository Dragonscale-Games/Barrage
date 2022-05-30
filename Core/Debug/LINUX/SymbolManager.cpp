/* ========================================================================= */
/*!
 *
 * \file            SymbolManager.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A debugging class to help load symbol information out of modules.
 *
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <stdafx.h>
#include <Debug/SymbolManager.hpp>

namespace Barrage
{
  SymbolManager::SymbolManager()
  {
  }

  SymbolManager::~SymbolManager()
  {
  }

  SymbolInfo SymbolManager::GetSymbolInfo(const void* address)
  {
    UNREFERENCED(address);
  }
}

