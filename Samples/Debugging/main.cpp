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
#include <iostream>
#include <intrin.h>

/****************************************************************************/
/*!
  \brief
    The entry point for testing debug features.
*/
/****************************************************************************/
int main()
{
  using namespace Barrage;
  SymbolManager symbolManager;
  SymbolInfo info = symbolManager.GetSymbolInfo(_ReturnAddress());
  // Print out the symbol information for this function.
  std::cout << "Symbol line: " << info.filepath_ << std::endl;
  __debugbreak();
  return 0;
}

#else

int main()
{
  return 0;
}

#endif
