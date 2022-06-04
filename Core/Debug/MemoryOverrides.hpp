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
#include <stdafx.h>
#include "MemoryDebugger.hpp"

void* operator new(std::size_t count)
{
  return memoryDebugger.Allocate(Barrage::AllocType::SINGLE, count, RETURN_ADDRESS());
}

void* operator new[](std::size_t count)
{
  return memoryDebugger.Allocate(Barrage::AllocType::ARRAY, count, RETURN_ADDRESS());
}

void* operator new(std::size_t count, const std::nothrow_t&) noexcept
{
  return memoryDebugger.Allocate(Barrage::AllocType::SINGLE, count, RETURN_ADDRESS());
}

void* operator new[](std::size_t count, const std::nothrow_t&) noexcept
{
  void* allocation = nullptr;
  try
  {
    allocation = 
      memoryDebugger.Allocate(Barrage::AllocType::ARRAY, count, RETURN_ADDRESS());
  }
  catch (std::bad_alloc&)
  {
  }

  return allocation;
}

void operator delete(void* ptr)
{
  memoryDebugger.Release(Barrage::AllocType::SINGLE, ptr);
}

void operator delete[](void* ptr)
{
  memoryDebugger.Release(Barrage::AllocType::ARRAY, ptr);
}

void operator delete(void* ptr, const std::nothrow_t&)
{
  memoryDebugger.Release(Barrage::AllocType::SINGLE, ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&)
{
  memoryDebugger.Release(Barrage::AllocType::ARRAY, ptr);
}

void operator delete(void* ptr, std::size_t count)
{
  UNREFERENCED(count);
  memoryDebugger.Release(Barrage::AllocType::SINGLE, ptr);
}

void operator delete[](void* ptr, std::size_t count)
{
  UNREFERENCED(count);
  memoryDebugger.Release(Barrage::AllocType::ARRAY, ptr);
}

////////////////////////////////////////////////////////////////////////////////
#endif // MemoryOverrides_MODULE_H
////////////////////////////////////////////////////////////////////////////////
