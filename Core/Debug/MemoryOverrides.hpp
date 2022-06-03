/* ========================================================================= */
/*!
 *
 * \file            MemoryOverrides.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * This file contains the definitions for overloading the memory
 * allocation operators. This file gets included by MemoryDebugger.hpp
 * to avoid defining these if the memory debugger never gets used.
 *
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef MemoryOverrides_MODULE_H
#define MemoryOverrides_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include "MemoryDebugger.hpp"

void* operator new(std::size_t count)
{
  NO_IMPL();
  UNREFERENCED(count);
  return malloc(count);
}

void* operator new[](std::size_t count)
{
  NO_IMPL();
  UNREFERENCED(count);
  return malloc(count);
}

void* operator new(std::size_t count, const std::nothrow_t&) noexcept
{
  NO_IMPL();
  UNREFERENCED(count);
  return malloc(count);
}

void* operator new[](std::size_t count, const std::nothrow_t&) noexcept
{
  NO_IMPL();
  UNREFERENCED(count);
  return malloc(count);
}

void operator delete(void* ptr)
{
  NO_IMPL();
  UNREFERENCED(ptr);
  free(ptr);
}

void operator delete[](void* ptr)
{
  NO_IMPL();
  UNREFERENCED(ptr);
  free(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&)
{
  NO_IMPL();
  UNREFERENCED(ptr);
  free(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&)
{
  NO_IMPL();
  UNREFERENCED(ptr);
  free(ptr);
}

void operator delete(void* ptr, std::size_t count)
{
  NO_IMPL();
  UNREFERENCED(ptr);
  UNREFERENCED(count);
  free(ptr);
}

void operator delete[](void* ptr, std::size_t count)
{
  NO_IMPL();
  UNREFERENCED(ptr);
  UNREFERENCED(count);
  free(ptr);
}

////////////////////////////////////////////////////////////////////////////////
#endif // MemoryOverrides_MODULE_H
////////////////////////////////////////////////////////////////////////////////
