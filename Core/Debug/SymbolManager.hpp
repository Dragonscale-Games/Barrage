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
#include <string>
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
    unsigned long line_;
  };
  //! The class responsible for managing symbol information.
  class SymbolManagerImpl
  {
  public:
    //! Forward declaration to the symbol manager that drives this implementation.
    friend class SymbolManager;

    /*************************************************************************/
    /*!
      \brief
        Initializes the symbol loading library from the operating system.
    */
    /*************************************************************************/
    SymbolManagerImpl();
    /*************************************************************************/
    /*!
      \brief
        Shuts down the symbol loading library.
    */
    /*************************************************************************/
    ~SymbolManagerImpl();
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
    SymbolInfo GetSymbolInfo(const void* address) const;
  };
  //! The starter for the symbol manager.
  class SymbolManager
  {
  public:
    
    /*************************************************************************/
    /*!
      \brief
        Creates a single local instance of the symbol manager.
        Initializes the global instance of the symbol manager if it hasn't
        already.
    */
    /*************************************************************************/
    SymbolManager();
    /*************************************************************************/
    /*!
      \brief
        Destroys a single local instance of the symbol manager.
        Destroys the global one if there are no other local instances
        to use it.
    */
    /*************************************************************************/
    ~SymbolManager();
    /*************************************************************************/
    /*!
      \brief
        Provides the symbol information given an instruction address.
      \param address
        The instruction address to query symbol information for.
      \returns
        A structure containing the symbol information for a
        given instruction address.
    */
    /*************************************************************************/
    static SymbolInfo GetSymbolInfo(const void* address);

  private:
    //! Create the memory necessary to store a manager but not actually create one.
    static SymbolManagerImpl* manager_;
    //! The reference count to make sure we only make one manager.
    static int referenceCount_;
  };
  //! The local instance of the symbol manager.
  static SymbolManager symbolManager;
}

#endif // SymbolManager_MODULE_H
