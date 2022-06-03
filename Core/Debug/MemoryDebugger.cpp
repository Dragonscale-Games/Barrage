/* ========================================================================= */
/*!
 *
 * \file            MemoryDebugger.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A debugging class to help catch memory problems.
 * Features of this class include:
 * - Throwing exceptions when users use deleted memory.
 * - Tracks allocated and release memory.
 * - Tracks errors created when deleting memory.
 * 
 * This file provides the common implementation for writing the statistics
 * to a file. Look in the MSVC/LINUX files for the OS-specific code.
 *
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <Debug/MemoryDebugger.hpp>

#include <fstream>
#include <cstdlib>
#include <array>

namespace
{
  constexpr int databaseLength = 4;
  template <typename T>
  using Database = std::array<T, databaseLength >;
}

namespace Barrage
{
  void* MemoryDebuggerImpl::Allocate(AllocType type, ptrdiff_t n) noexcept(false)
  {
    UNREFERENCED(type);
    UNREFERENCED(n);
    return nullptr;
  }

  void MemoryDebuggerImpl::Release(void* address)
  {
    UNREFERENCED(address);
  }
  
  void MemoryDebuggerImpl::DumpMemoryStats(const char* filepath, MemStat flags)
  {
    // A table with the lists associated with each statistic.
    const Database<AllocList*> statList = {
      &allocated_, &deleted_, &doubleDeleted_, &mismatched_,
    };
    // A table containing all possible stats.
    const Database<MemStat> availableStats = {
      MemStat::CURRENTLY_ALLOCATED,
      MemStat::CURRENTLY_DELETED,
      MemStat::DOUBLE_DELETES,
      MemStat::MISMATCHED_DELETES,
    };
    // A table containing all the labels for the stats.
    const Database<const char* const> labels = {
      "Allocate", "Delete", "Double Delete", "Mismatched Delete"
    };
    assert(statList.size() == availableStats.size());
    // Create the file to dump our statistics.
    std::ofstream statFile;
    statFile.open(filepath);
    if (statFile)
    {
      size_t length = statList.size();
      DumpStatHeader(statFile);
      // If we are printing all of them then walk through the entire
      // table.
      for (size_t i = 0; i < length; ++i)
      {
        if (static_cast<uint8_t>(flags) & static_cast<uint8_t>(availableStats[i]))
        {
          DumpList(statFile, *statList[i], labels[i]);
        }
      }
    }
    else
    {
      std::cout << "Failed to create the statistics file." << std::endl;
    }
    statFile.close();
  }

  void MemoryDebuggerImpl::DumpList(std::ofstream& statFile, const AllocList& list, const char* entryLabel)
  {
    assert(statFile);
    assert(entryLabel);
    for (auto iter = list.cbegin(); iter != list.cend(); ++iter)
    {
      const Allocation& allocation = *iter;
      DumpAllocation(statFile, allocation, entryLabel);
    }
  }

  void MemoryDebuggerImpl::DumpStatHeader(std::ofstream& statFile)
  {
    assert(statFile);
    statFile << "Status, Allocation Size, Memory Address, File" << std::endl;
  }

  void MemoryDebuggerImpl::DumpAllocation(
    std::ofstream& statFile, const Allocation& allocation, const char* entryLabel)
  {
    statFile << entryLabel << ", ";
    statFile << allocation.allocSize_ << ", ";
    statFile << allocation.allocation_ << ", ";
    statFile << allocation.file_.c_str() << ", ";
  }
}

