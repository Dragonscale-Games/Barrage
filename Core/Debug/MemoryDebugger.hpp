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

#include <Utilities/Mallocator.hpp>
#include <Debug/SymbolManager.hpp>

namespace Barrage
{
  //! The enumeration for the statistics tracked by the memory debugger.
  enum MemStat
  {
    CURRENTLY_ALLOCATED = 0x01,
    CURRENTLY_DELETED = 0x02,
    DOUBLE_DELETES = 0x04,
    MISMATCHED_DELETES = 0x08,
    UNALLOCATED_DELETES = 0x10,
    ALL = 0xFF,
    COUNT = 5,
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
    friend class MemoryDebugger;
    static const size_t FourK = 4096u;

    /*************************************************************************/
    /*!
      \brief
        Creates a default constructor for the implementation for
        the memory debugger.
    */
    /*************************************************************************/
    MemoryDebuggerImpl();
    /*************************************************************************/
    /*!
      \brief
        Releases all pages allocated throughout tracking.
    */
    /*************************************************************************/
    ~MemoryDebuggerImpl();
    /*************************************************************************/
    /*!
      \brief
        Allocates a page and returns a memory address n bytes away from
        a page boundary.
      \param type
        The type of memory allocation being made.
      \param n
        The distance away from the memory boundary in bytes.
      \param allocAddress
        The instruction address which called the allocation function.
      \throws std::bad_alloc
        Whenever the user allocates for a size the operating system
        cannot not offer.
    */
    /*************************************************************************/
    void* Allocate(AllocType type, size_t n, const void* allocAddress) noexcept(false);
    /*************************************************************************/
    /*!
      \brief
        Frees the memory address specified and uncommiting the page
        associated with it.
      \param type
        The type of memory allocation being released.
      \param address
        The memory address to free.
    */
    /*************************************************************************/
    void Release(AllocType type, const void* address);

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
    void DumpMemoryStats(const char* filepath, int flags = MemStat::ALL);

  private:
    static MemoryDebuggerImpl* instance_;
    //! The list keeping track of currently allocated objects.
    AllocList allocated_;
    //! The list keeping track of all deleted objects.
    AllocList deleted_;
    //! The list keeping track of all double deleted objects.
    AllocList doubleDeleted_;
    //! The list keeping track of all mismatched deletes.
    AllocList mismatched_;
    //! The list maintaining unallocated deletes.
    AllocList unallocDeleted_;

    /*************************************************************************/
    /*!
      \brief
        Dumps the header of the csv file.
      \param statFile
        The header of the statistics file.
    */
    /*************************************************************************/
    static void DumpStatHeader(std::ofstream& statFile);
    /*************************************************************************/
    /*!
      \brief
        Dumps the allocation list to a statistics file.
      \param statFile
        A pointer to the file opened to write the list.
      \param list
        The list to dump.
      \param entryLabel
        The status label for every entry on this list.
    */
    /*************************************************************************/
    static void DumpList(std::ofstream& statFile, const AllocList& list, const char* entryLabel);
    /*************************************************************************/
    /*!
      \brief
        Dumps an allocation to a statistics file.
      \param statFile
        A pointer to the file opened to write the allocation in.
      \param allocation
        The allocation to write to the file.
      \param entryLabel
        The label for the allocationo entry being written.
    */
    /*************************************************************************/
    static void DumpAllocation(std::ofstream& statFile, const Allocation& allocation, const char* entryLabel);

    /*************************************************************************/
    /*!
      \brief
        Creates an allocation using a memory page.
        Commiting from a page helps combat invalid reads and writes but
        also allocates a multiple of a page's size (typically 4 kilobytes) no
        matter the allocation size.
      \param size
        The size of the allocation made.
      \returns
        A pointer to the page allocated. On a failure, the allocation
        field on the structure will be a null pointer.
    */
    /*************************************************************************/
    static void* AllocatePage(size_t size);
    /*************************************************************************/
    /*!
      \brief
        Decommisions a page. If the user attempts to access the 
        memory from this page again, they will get a hardware exception.
      \param page
        The page to decommision.
      \returns
        True if successful, false if errors were created in the attempt.
    */
    /*************************************************************************/
    static bool DecommisionPage(void* page);
    /*************************************************************************/
    /*!
      \brief
        Releases the page back to the operating system. Once this happens
        there is no safety nets for the user if they access the memory
        again.
      \param page
        The page to release.
      \returns
        True if successful, otherwise there were errors.
    */
    /*************************************************************************/
    static bool ReleasePage(void* page);
    /*************************************************************************/
    /*!
      \brief
        Finds whether an allocation address is already in a list.
      \param list
        The list to check for the address.
      \param address
        The address to check in the list.
      \returns
        A constant iterator which returns the position in the list
        if the address is found.
        Otherwise, it returns one element past the end of the list.
    */
    /*************************************************************************/
    AllocList::const_iterator FindAddressIn(const AllocList& list, const void* address);
    /*************************************************************************/
    /*!
      \brief
        Calculates the number of pages to house a given allocation size.
        Passing in a size of zero is invalid to calculate the page 
        count.
      \param size
        The size of the allocation.
      \returns
        The number of pages to allocate.
    */
    /*************************************************************************/
    static size_t CalculatePageCount(size_t size);
    /*************************************************************************/
    /*!
      \brief
        Calculates the size of the page allocation in bytes.
      \param size
        The size of the allocation.
      \returns
        The number of bytes to allocate for the pages.
    */
    /*************************************************************************/
    static size_t CalculatePageSize(size_t size);
    /*************************************************************************/
    /*!
      \brief
        Calculates the position of the allocation within the page.
      \param page
        The page to calculate the offset to.
      \param size
        The size of the allocation itself.
    */
    /*************************************************************************/
    static void* GetPositionInPage(void* page, size_t size);
  };
  //! The starter for the memory manager.
  class MemoryDebugger
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Initializes the local instance of the memory debugger.
        Creates the static global implementation of the debugger.
    */
    /*************************************************************************/
    MemoryDebugger();
    /*************************************************************************/
    /*!
      \brief
        Destroys the local instance of the memory debugger.
        Destroys the static global implementation of the debugger.
    */
    /*************************************************************************/
    ~MemoryDebugger();
    /*************************************************************************/
    /*!
      \brief
        Allocates a page and returns a memory address n bytes away from
        a page boundary.
      \param type
        The type of memory allocation being made.
      \param n
        The distance away from the memory boundary in bytes.
      \param allocAddress
        The instruction address which called the allocation function.
      \throws std::bad_alloc
        Whenever the user allocates for a size the operating system
        cannot not offer.
    */
    /*************************************************************************/
    static void* Allocate(AllocType type, size_t n, const void* allocAddress) noexcept(false);
    /*************************************************************************/
    /*!
      \brief
        Frees the memory address specified and uncommiting the page
        associated with it.
      \param type
        The type of memory allocation being released.
      \param address
        The memory address to free.
    */
    /*************************************************************************/
    static void Release(AllocType type, const void* address);

  private:
    // Create the memory necessary to store one debugger but not actually create one yet.
    static MemoryDebuggerImpl* debugger_;
    //! The reference count to make sure we only make one debugger.
    static int referenceCount_;
  };
  //! The single instance of the memory debugger.
  static MemoryDebugger memoryDebugger;
}

////////////////////////////////////////////////////////////////////////////////
#endif // MemoryDebugger_MODULE_H
////////////////////////////////////////////////////////////////////////////////
