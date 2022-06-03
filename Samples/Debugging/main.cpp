/* ======================================================================== */
/*!
 * \file            main.cpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
   A sample file showing the debugging features Barrage has available.
 */
/* ======================================================================== */

/* ======================================================================== */
/* Includes */
/* ======================================================================== */

#ifdef _WIN32

#include <Debug/SymbolManager.hpp>
#include <Debug/MemoryDebugger.hpp>
/*****************************************************************************/
/* The overrides for the new and delete operators offered by C++ */
/*****************************************************************************/
#include <Debug/MemoryOverrides.hpp>
#include <iostream>
#include <intrin.h>

#ifdef __clang__
#define RETURN_ADDRESS() __builtin_return_address(0)
#else
#define RETURN_ADDRESS() _ReturnAddress()
#endif

/****************************************************************************/
/*!
  \brief
    Runs a demo for using the symbol manager.
*/
/****************************************************************************/
void SymbolDemo();
/****************************************************************************/
/*!
  \brief
    Runs a demo for using the memory debugger.
*/
/****************************************************************************/
void MemoryDemo();
/****************************************************************************/
/*!
  \brief
    The entry point for testing debug features.
*/
/****************************************************************************/
int main()
{
  SymbolDemo();
  MemoryDemo();
  __debugbreak();
  return 0;
}

void SymbolDemo()
{
  Barrage::SymbolInfo info = Barrage::symbolManager.GetSymbolInfo(RETURN_ADDRESS());
  // Print out the symbol information for this function.
  std::cout << "Symbols for the return address in SymbolDemo: " << info.filepath_ << std::endl;
}

void MemoryDemo()
{
  Barrage::MemoryDebuggerImpl memoryDebugger;
  void* address = memoryDebugger.Allocate(Barrage::AllocType::SINGLE, 40u);
  void* allocated = new int[4];
  UNREFERENCED(allocated);
  // and whoops there goes some memory...
  memoryDebugger.DumpMemoryStats("memory_stats.csv");
  memoryDebugger.Release(address);
  // ... hopefully this will get tracked c:
  memoryDebugger.DumpMemoryStats("memory_stats.csv");
}

#else

int main()
{
  return 0;
}

#endif
