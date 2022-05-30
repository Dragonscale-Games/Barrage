/* ========================================================================= */
/*!
 *
 * \file            MemoryDebugger.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A debugging class to help catch memory problems.
 * Features of this class include:
 * - Throwing exceptions when users use deleted memory.
 * - Tracks allocated and release memory.
 * - Tracks errors created when deleting memory.
 * 
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef MemoryDebugger_MODULE_H
#define MemoryDebugger_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <stddef.h>
#include <list>
#include <Debug/SymbolManager.hpp>
#include <Utilities/Mallocator.hpp>

namespace Barrage
{
  //! The enumeration for the statistics tracked by the memory debugger.
  enum class MemStat : uint8_t
  {
    CURRENTLY_ALLOCATED = 0x01,
    CURRENTLY_DELETED = 0x02,
    DOUBLE_DELETES = 0x04,
    MISMATCHED_DELETES = 0x08,
    ALL = 0xFF
  };
  //! The enumeration for the kinds of allocations possible to track.
  enum class AllocType
  {
    SINGLE,
    ARRAY,
  };
  //! The structure to encapsulate the metadata of each allocation.
  struct Allocation
  {
    //! The type of allocation made.
    AllocType type_;
    //! The size of the allocation made.
    size_t allocSize_;
    //! The pointer to the page made for this allocation.
    void* page_;
    //! The pointer to the allocation.
    void* allocation_;
    //! The name of the file that allocated the object.
    MallocString file_;
  };
  //! The type defintion for an allocation list.
  using AllocList = std::list<Allocation, Mallocator<Allocation> >;

  //! The class in charge of keep track of memory allocations.
  class MemoryDebuggerImpl
  {
  public:
    
    /*************************************************************************/
    /*!
      \brief
        Allocates a page and returns a memory address n bytes away from
        a page boundary.
      \param type
        The type of memory allocation being made.
      \param n
        The distance away from the memory boundary in bytes.
    */
    /*************************************************************************/
    void* Allocate(AllocType type, ptrdiff_t n);
    /*************************************************************************/
    /*!
      \brief
        Frees the memory address specified and uncommiting the page
        associated with it.
      \param address
        The memory address to free.
    */
    /*************************************************************************/
    void Release(void* address);

    /*************************************************************************/
    /*!
      \brief
        Dumps all mismatched memory deletes.
      \param filepath
        The filepath to dump the csv file.
      \param flags
        Flags for the function denoting which statistics to dump.
    */
    /*************************************************************************/
    void DumpMemoryStats(const char* filepath, MemStat flags = MemStat::ALL);

  private:
    //! The list keeping track of currently allocated objects.
    AllocList allocated_;
    //! The list keeping track of all deleted objects.
    AllocList deleted_;
    //! The list keeping track of all double deleted objects.
    AllocList doubleDeleted_;
    //! The list keeping track of all mismatched deletes.
    AllocList mismatched_;

    /*************************************************************************/
    /*!
      \brief
        Dumps the header of the csv file.
      \param file
        The header of the statistics file.
    */
    /*************************************************************************/
    static void DumpStatHeader(FILE* file);
    /*************************************************************************/
    /*!
      \brief
        Dumps the allocation list to a csv file.
      \param file
        A pointer to the file opened to write the list.
      \param list
        The list to dump.
      \param entryLabel
        The status label for every entry on this list.
    */
    /*************************************************************************/
    static void DumpList(FILE* file, const AllocList& list, const char* entryLabel);
  };
}

#endif