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
#include <Debug/SymbolManager.hpp>

#include <algorithm>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <array>

namespace
{
  template <typename T>
  using Database = std::array<T, (uint8_t)Barrage::MemStat::COUNT >;
}

namespace Barrage
{
  int MemoryDebugger::referenceCount_ = 0;
  MemoryDebuggerImpl* MemoryDebugger::debugger_ = nullptr;

  MemoryDebuggerImpl::MemoryDebuggerImpl()
  {
  }

  MemoryDebuggerImpl::~MemoryDebuggerImpl()
  {
    // Finally, release all of our allocated pages.
    for (Allocation& allocation : deleted_)
    {
      ReleasePage(allocation.pageData_);
    }
  }

  void* MemoryDebuggerImpl::Allocate(AllocType type, size_t n, const void* allocAddress) noexcept(false)
  {
    Allocation allocation = {};
    PageAllocation pageAllocation = AllocatePage(n);
    // Check if we successfully made an allocation.
    if (!pageAllocation.page_)
    {
      throw std::bad_alloc();
    }
    else
    {
      SymbolInfo symbol = SymbolManager::GetSymbolInfo(allocAddress);
      std::basic_stringstream<char, std::char_traits<char>, Mallocator<char> > symbolNameBuild;
      symbolNameBuild << symbol.filepath_;
      symbolNameBuild << ":" << symbol.line_;
      // When we have an allocated page, we fill out the rest of the allocation
      // structure.
      allocation.type_ = type;
      allocation.allocSize_ = n;
      allocation.pageData_ = pageAllocation;
      allocation.allocation_ = GetPositionInPage(pageAllocation.page_, n);
      allocation.file_ = symbolNameBuild.str().c_str();
    }
    // Upon success, we add our allocation to a list and return the allocation.
    allocated_.push_back(allocation);
    return allocation.allocation_;
  }

  void MemoryDebuggerImpl::Release(AllocType type, const void* address)
  {
    // Find the allocation address within our list.
    auto allocatedIter = FindAddressIn(allocated_, address);
    if (allocatedIter != allocated_.cend())
    {
      // We first check whether we actually have deleted this address before.
      auto iter = FindAddressIn(deleted_, address);
      if (iter != deleted_.cend())
      {
        // At this point we know the user attempted to delete a previously deleted address.
        doubleDeleted_.push_back(*iter);
        BREAKPOINT();
      }
      else
      {
        // Otherwise, we decommision page storing it and keep track of our allocation.
        bool isDecommisionSuccess = DecommisionPage(allocatedIter->pageData_);
        if (!isDecommisionSuccess)
        {
          BREAKPOINT();
        }
        // Mark the allocation as deleted.
        deleted_.push_back(*allocatedIter);
        // Check if we have a mismatch delete on our hands.
        if (allocatedIter->type_ != type)
        {
          mismatched_.push_back(*allocatedIter);
          BREAKPOINT();
        }
        // Remove the allocated entry from the list.
        allocated_.erase(allocatedIter);
      }
    }
    else
    {
      // Otherwise, we attempted to delete something that wasn't allocated.
      // The result could be...
      // A double delete..?
      auto iter = FindAddressIn(deleted_, address);
      if (iter != deleted_.cend())
      {
        // Log our double delete.
        doubleDeleted_.push_back(*iter);
        BREAKPOINT();
      }
      // Or we attempted to delete something we didn't even allocate.
      else
      {
        // Log our mysterious delete.
        unallocDeleted_.push_back(*iter);
        BREAKPOINT();
      }
    }
  }
  
  void MemoryDebuggerImpl::DumpMemoryStats(const char* filepath, int flags)
  {
    // A table with the lists associated with each statistic.
    const Database<AllocList*> statList = {
      &allocated_, &deleted_, &doubleDeleted_, &mismatched_, &unallocDeleted_,
    };
    // A table containing all possible stats.
    const Database<MemStat> availableStats = {
      MemStat::CURRENTLY_ALLOCATED,
      MemStat::CURRENTLY_DELETED,
      MemStat::DOUBLE_DELETES,
      MemStat::MISMATCHED_DELETES,
      MemStat::UNALLOCATED_DELETES,
    };
    // A table containing all the labels for the stats.
    const Database<const char* const> labels = {
      "Allocated", "Deleted", "Double Delete", "Mismatched Delete", "Unallocated Delete"
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
    statFile << std::endl;
  }

  AllocList::iterator MemoryDebuggerImpl::FindAddressIn(AllocList& list, const void* address)
  {
    const auto findOnAddressMatch = [&address](Allocation& allocation)
    {
      return allocation.allocation_ == address;
    };
    // Find the allocation address within our list.
    auto iter = std::find_if(list.begin(), list.end(), findOnAddressMatch);
    return iter;
  }

  size_t MemoryDebuggerImpl::CalculatePageCount(size_t size)
  {
    return size / FourK + 1u * ((size % FourK) != 0);
  }

  size_t MemoryDebuggerImpl::CalculatePageSize(size_t size)
  {
    return CalculatePageCount(size) * FourK * sizeof(unsigned char);
  }

  void* MemoryDebuggerImpl::GetPositionInPage(void* page, size_t size)
  {
    return static_cast<unsigned char*>(page) + CalculatePageSize(size) - size;
  }

  MemoryDebugger::MemoryDebugger()
  {
    if (++referenceCount_ == 1)
    {
      // Manually call the constructor for the symbol manager.
      debugger_ = static_cast<MemoryDebuggerImpl*>(malloc(sizeof(MemoryDebuggerImpl)));
      debugger_ = new (debugger_) MemoryDebuggerImpl;
    }
  }

  MemoryDebugger::~MemoryDebugger()
  {
    if (referenceCount_-- == 1)
    {
      // Print out any memory leaks by this point.
      debugger_->DumpMemoryStats("memory_log.csv", Barrage::MemStat::ALL & ~Barrage::MemStat::CURRENTLY_DELETED);
      // Manually release the resources called by the manager.
      debugger_->~MemoryDebuggerImpl();
      free(debugger_);
      debugger_ = nullptr;
    }
  }

  void* MemoryDebugger::Allocate(AllocType type, size_t n, const void* allocAddress) noexcept(false)
  {
    assert(debugger_);
    if (debugger_)
    {
      return debugger_->Allocate(type, n, allocAddress);
    }
    else
    {
      throw std::bad_alloc();
    }
  }

  void MemoryDebugger::Release(AllocType type, const void* address)
  {
    assert(debugger_);
    if (debugger_)
    {
      debugger_->Release(type, address);
    }
  }
}
