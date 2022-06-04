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
  void* MemoryDebuggerImpl::AllocatePage(size_t size)
  {
    return nullptr;
  }

  bool MemoryDebuggerImpl::DecommisionPage(void* page)
  {
    NO_IMPL();
    UNREFERENCED(page);
    return false;
  }

  bool MemoryDebuggerImpl::ReleasePage(void* page)
  {
    NO_IMPL();
    UNREFERENCED(page);
    return false;
  }
}
