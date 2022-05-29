/* ========================================================================= */
/*!
 *
 * \file            MemoryDebugger.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A debugging class to help catch memory problems.
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
#include "Utilities/Mallocator.hpp"

namespace Barrage
{
  //! The enumeration for the kinds of allocations possible to track.
  enum class AllocType
  {
    SINGLE,
    ARRAY,
  };
  //! The structure to encapsulate the metadata of each allocation.
  struct Allocation
  {
    //! The size of the allocation made.
    size_t allocSize_;
    //! The type of allocation made.
    AllocType type_;
    //! The pointer to the page made for this allocation.
    void* page_;
    //! The pointer to the allocation.
    void* allocation_;
    //! The name of the file that allocated the object.
    MallocString file_;
  };
  //! The type defintion for an allocation list.
  using AllocList = std::list<Mallocator<Allocation> >;
  //! The class in charge of keep track of memory allocations.
  class MemoryDebugger
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Creates an instance of the memory debugger.
    */
    /*************************************************************************/
    MemoryDebugger();
    /*************************************************************************/
    /*!
      \brief
        Destroys the memory debugger and dumps the every wrong memory 
        operation into a csv file.
    */
    /*************************************************************************/
    ~MemoryDebugger();

    /*************************************************************************/
    /*!
      \brief
        Allocates a page and returns a memory address n bytes away from
        a page boundary.
      \param n
        The distance away from the memory boundary in bytes.
    */
    /*************************************************************************/
    void* Allocate(ptrdiff_t n);
    /*************************************************************************/
    /*!
      \brief
        Frees the memory address specified and uncommiting the page
        associated with it.
      \param address
        The memory address to free.
    */
    /*************************************************************************/
    void Free(void* address);

    /*************************************************************************/
    /*!
      \brief
        Dumps all mismatched memory deletes.
      \param filepath
        The filepath to dump the csv file.
    */
    /*************************************************************************/
    void DumpMismatchedDeletes(const char* filepath);
    /*************************************************************************/
    /*!
      \brief
        Dumps all double memory deletes.
      \param filepath
        The filepath to dump the csv file.
    */
    /*************************************************************************/
    void DumpDoubleDeletes(const char* filepath);

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
        Dumps the allocation list to a csv file.
      \param list
        The list to dump.
      \param filepath
        The path given to dump the csv file.
    */
    /*************************************************************************/
    static void DumpList(const AllocList& list, const char* filepath);
  };
}

#endif