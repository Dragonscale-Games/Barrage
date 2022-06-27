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

#include <stdafx.h>
#include <iostream>
#include <Debug/SymbolManager.hpp>
#include <Debug/MemoryDebugger.hpp>
/*****************************************************************************/
/* The overrides for the new and delete operators offered by C++ */
/*****************************************************************************/
#include <Debug/MemoryOverrides.hpp>

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
  BREAKPOINT();
  return 0;
}

void SymbolDemo()
{
  /*
  Barrage::SymbolInfo info = Barrage::symbolManager.GetSymbolInfo(RETURN_ADDRESS());
  // Print out the symbol information for this function.
  std::cout << "Symbols for the return address in SymbolDemo: " << info.filepath_ << std::endl;
  */
}

void MemoryDemo()
{
  int* allocated = new int[4]();
  UNREFERENCED(allocated);
  // and whoops there goes some memory...
  allocated = new int[4]();
  //memoryDebugger.Release(address);
  // ... hopefully this will get tracked c:
  //allocated[5] = 0;
  delete allocated;
}
