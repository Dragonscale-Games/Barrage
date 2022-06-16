/* ========================================================================= */
/*!
 *
 * \file            MemoryDebugger.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * The MSVC-specific implementation for the memory debugger.
 *
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <stdafx.h>
#include <Debug/MemoryDebugger.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memoryapi.h>

namespace Barrage
{
  PageAllocation MemoryDebuggerImpl::AllocatePage(size_t size)
  {
    // Get a page from the windows operating system.
    const size_t pageSize = CalculatePageSize(size);
    void* page = VirtualAlloc(NULL, pageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    PageAllocation pageData = { };
    pageData.pageSize_ = pageSize;
    pageData.page_ = page;
    return pageData;
  }

  bool MemoryDebuggerImpl::DecommisionPage(PageAllocation& page)
  {
    return VirtualFree(page.page_, 0u, MEM_DECOMMIT);
  }

  bool MemoryDebuggerImpl::ReleasePage(PageAllocation& page)
  {
    return VirtualFree(page.page_, 0u, MEM_RELEASE);
  }
}

