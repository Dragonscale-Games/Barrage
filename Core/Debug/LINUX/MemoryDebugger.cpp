/* ========================================================================= */
/*!
 *
 * \file            MemoryDebugger.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * The Linux-specific implementation for the memory debugger.
 *
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <stdafx.h>
#include <Debug/MemoryDebugger.hpp>

namespace Barrage
{
  Allocation MemoryDebuggerImpl::Commision(size_t size)
  {
    Allocation allocation = {};
    allocation.allocation_ = nullptr;
    return allocation;
  }

  bool MemoryDebuggerImpl::Decommision(Allocation allocation)
  {
    UNREFERENCED(allocation);
    return false;
  }
}

