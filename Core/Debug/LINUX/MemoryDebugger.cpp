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
  Allocation MemoryDebuggerImpl::AllocatePage(size_t size)
  {
    Allocation allocation = {};
    allocation.allocation_ = nullptr;
    return allocation;
  }

  bool MemoryDebuggerImpl::DecommisionPage(const Allocation& allocation)
  {
    NO_IMPL();
    UNREFERENCED(allocation);
    return false;
  }

  bool MemoryDebuggerImpl::ReleasePage(const Allocation& allocation)
  {
    NO_IMPL();
    UNREFERENCED(allocation);
    return false;
  }
}
