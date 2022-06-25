/* ========================================================================= */
/*!
 *
 * \file            LINUX/MemoryDebugger.cpp
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

#include <sys/mman.h>

namespace Barrage
{
  PageAllocation MemoryDebuggerImpl::AllocatePage(size_t size)
  {
    PageAllocation pageData = { };
    pageData.pageSize_ = CalculatePageSize(size);
    pageData.page_ = 
      mmap(NULL, pageData.pageSize_, PROT_WRITE | PROT_READ, MAP_SHARED, 0, 0);
    // If there was an error, the kernel returns -1 as a pointer.
    if(pageData.page_ == reinterpret_cast<void*>(-1))
    {
      // For the debugger to know there was an error, we return a nullptr.
      pageData.page_ = nullptr;
    }
    return pageData;
  }

  bool MemoryDebuggerImpl::DecommisionPage(PageAllocation& page)
  {
    void* pageCode = mmap(page.page_, page.pageSize_, 0, MAP_SHARED, 0, 0);
    return pageCode != reinterpret_cast<void*>(-1);
  }

  bool MemoryDebuggerImpl::ReleasePage(PageAllocation& page)
  {
    int errorCode = munmap(page.page_, page.pageSize_);
    return errorCode != -1;
  }
}
