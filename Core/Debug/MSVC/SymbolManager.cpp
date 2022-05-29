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

namespace Barrage
{
  SymbolManager::SymbolManager()
  {
    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
    HANDLE process = GetCurrentProcess();
    BOOL result = SymInitialize(process, NULL, true);
    if (!result)
    {
      // Failed to load symbols on this process.
      DebugBreak();
    }
  }

  SymbolManager::~SymbolManager()
  {
  }

  SymbolInfo SymbolManager::GetSymbolInfo(const void* address)
  {
    SymbolInfo info = {};
    HANDLE process = GetCurrentProcess();
    IMAGEHLP_LINE64 winSymbols = {};
    DWORD displacement = 0;
    DWORD64 lineAddress = reinterpret_cast<DWORD64>(address);
    
    winSymbols.SizeOfStruct = sizeof(winSymbols);
    
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
      DebugBreak();
    }

    return info;
  }
}

