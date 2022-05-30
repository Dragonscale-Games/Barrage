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
  //! The type defintion for the mallocator string.
  using MallocString = std::basic_string<char, std::char_traits<char>, Mallocator<char> >;

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
  private:
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
    
    SymbolManager() : manager_(nullptr)
    {
      if (++referenceCount_ == 1)
      {
        // Manually call the constructor for the symbol manager.
        manager_ = static_cast<SymbolManagerImpl*>(malloc(sizeof(SymbolManagerImpl)));
        new (&manager_) SymbolManagerImpl;
      }
    }

    ~SymbolManager()
    {
      if (referenceCount_-- == 1)
      {
        // Manually release the resources called by the manager.
        manager_->~SymbolManagerImpl();
        free(manager_);
        manager_ = nullptr;
      }
    }

    SymbolInfo GetSymbolInfo(void* address) const
    {
      return (*manager_).GetSymbolInfo(address);
    }

  private:
    // Create the memory necessary to store a manager but not actually create one.
    SymbolManagerImpl* manager_;
    static int referenceCount_;
  };

  static SymbolManager symbolManager;
}

#endif // SymbolManager_MODULE_H
