/* ========================================================================= */
/*!
 *
 * \file            Debug/SymbolManager.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A debugging class to help load symbol information out of modules.
 * This file implements to OS-agnostic parts of the manager.
 *
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include "SymbolManager.hpp"

namespace Barrage
{
  int SymbolManager::referenceCount_ = 0;
  SymbolManagerImpl* SymbolManager::manager_ = nullptr;

  SymbolManager::SymbolManager()
  {
    if (++referenceCount_ == 1)
    {
      // Manually call the constructor for the symbol manager.
      SymbolManager::manager_ = static_cast<SymbolManagerImpl*>(malloc(sizeof(SymbolManagerImpl)));
      SymbolManager::manager_ = new (SymbolManager::manager_) SymbolManagerImpl;
    }
  }

  SymbolManager::~SymbolManager()
  {
    if (referenceCount_-- == 1)
    {
      // Manually release the resources called by the manager.
      SymbolManager::manager_->~SymbolManagerImpl();
      free(SymbolManager::manager_);
      SymbolManager::manager_ = nullptr;
    }
  }

  SymbolInfo SymbolManager::GetSymbolInfo(const void* address)
  {
    assert(manager_);
    return manager_->GetSymbolInfo(address);
  }
}
