/* ========================================================================= */
/*!
 *
 * \file            SymbolManager.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A debugging class to help load symbol information out of modules.
 *
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include <stdafx.h>
#include <Debug/SymbolManager.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <DbgHelp.h>
#include <intrin.h>

namespace Barrage
{
  SymbolManagerImpl::SymbolManagerImpl()
  {
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
    HANDLE process = GetCurrentProcess();
    BOOL result = SymInitialize(process, NULL, TRUE);
    if (!result)
    {
      // Get the error for the symbol manager.
      DWORD error = GetLastError();
      std::cout << "Failed to initialize symbol loading in Windows (error code: "
        << error << ")" << std::endl;
      // Failed to load symbols on this process.
      BREAKPOINT();
    }
  }

  SymbolManagerImpl::~SymbolManagerImpl()
  {
  }

  SymbolInfo SymbolManagerImpl::GetSymbolInfo(const void* address) const
  {
    SymbolInfo info = {};
    HANDLE process = GetCurrentProcess();
    IMAGEHLP_LINE64 winSymbols = {};
    DWORD displacement = 0;
    DWORD64 lineAddress = reinterpret_cast<DWORD64>(address);
    
    winSymbols.SizeOfStruct = sizeof(winSymbols);
    
    SymSetOptions(SYMOPT_LOAD_LINES);
    BOOL result = SymGetLineFromAddr64(process, lineAddress, &displacement, &winSymbols);
    if (result)
    {
      info.filepath_ = winSymbols.FileName;
      info.address_ = reinterpret_cast<void*>(winSymbols.Address);
      info.line_ = winSymbols.LineNumber;
    }
    else
    {
      // We passed a memory address not within our code base.
      BREAKPOINT();
    }

    return info;
  }
}
