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
  PageAllocation MemoryDebuggerImpl::AllocatePage(size_t size)
  {
    PageAllocation pageData = { };
    pageData.pageSize_ = 0;
    pageData.page_ = nullptr;
    return pageData;
  }

  bool MemoryDebuggerImpl::DecommisionPage(PageAllocation& page)
  {
    NO_IMPL();
    UNREFERENCED(page);
    return false;
  }

  bool MemoryDebuggerImpl::ReleasePage(PageAllocation& page)
  {
    NO_IMPL();
    UNREFERENCED(page);
    return false;
  }
}
