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

namespace Barrage
{
  FILE* MemoryDebuggerImpl::OpenDumpFile(const char* filepath)
  {
    FILE* statFile = NULL;
    errno_t error = fopen_s(&statFile, filepath, "wt");
    // Not sure if this is necessary, but just in case...
    if (error != 0)
    {
      statFile = NULL;
    }
    return statFile;
  }

  void MemoryDebuggerImpl::DumpStatHeader(FILE* statFile)
  {
    assert(statFile);
    fprintf_s(statFile, "Status, Allocation Size, Memory Address, File\n");
  }

  void MemoryDebuggerImpl::DumpAllocation(
    FILE* statFile, const Allocation& allocation, const char* entryLabel)
  {
    assert(statFile);
    assert(entryLabel);
    fprintf_s(statFile, "%s, %lu, %p, %s",
      entryLabel,
      allocation.allocSize_,
      allocation.allocation_,
      allocation.file_.c_str());
  }
}

