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
  FILE* MemoryDebuggerImpl::OpenDumpFile(const char* filepath)
  {
    FILE* statFile = fopen(filepath, "wt");
    return statFile;
  }

  void MemoryDebuggerImpl::DumpStatHeader(FILE* statFile)
  {
    assert(statFile);
    fprintf(statFile, "Status, Allocation Size, Memory Address, File\n");
  }

  void MemoryDebuggerImpl::DumpAllocation(
    FILE* statFile, const Allocation& allocation, const char* entryLabel)
  {
    assert(statFile);
    assert(entryLabel);
    fprintf(statFile, "%s, %lu, %p, %s",
      entryLabel,
      allocation.allocSize_,
      allocation.allocation_,
      allocation.file_.c_str());
  }
}

