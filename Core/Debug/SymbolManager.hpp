/* ========================================================================= */
/*!
 *
 * \file            SymbolManager.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A debugging class to help load symbol information out of modules.
 * 
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef SymbolManager_MODULE_H
#define SymbolManager_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <Utilities/Mallocator.hpp>

namespace Barrage
{
  //! The structure maintaining symbol information for a single memory address.
  struct SymbolInfo
  {
    //! The path to the file the memory address goes to.
    MallocString filepath_;
    //! The memory address with the related info.
    const void* address_;
    //! The line number the memory address comes from.
    short line_;
  };
  //! The class responsible for managing symbol information.
  class SymbolManager
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Initializes the symbol loading library from the operating system.
    */
    /*************************************************************************/
    SymbolManager();
    /*************************************************************************/
    /*!
      \brief
        Shuts down the symbol loading library.
    */
    /*************************************************************************/
    ~SymbolManager();
    /*************************************************************************/
    /*!
      \brief
        Gets the symbol information from a memory address in an address
        space present in a module.
      \param address
        The memory address given in a module spce.
      \returns
        A structure with the information of the memory address.
    */
    /*************************************************************************/
    SymbolInfo GetSymbolInfo(const void* address);
 };
}

#endif // SymbolManager_MODULE_H
