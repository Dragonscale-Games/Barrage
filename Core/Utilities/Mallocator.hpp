/* ======================================================================== */
/*!
 * \file            Mallocator.hpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             david.wongcascante\@gmail.com

 * \brief
   A helper class to use standard containers using the c runtime heap.
   Helps create classes that track of allocations made using new and delete.
   Read more about the mallocator with this article:
   https://devblogs.microsoft.com/cppblog/the-mallocator/
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Mallocator_BARRAGE_H
#define Mallocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

/* ======================================================================== */
/* Includes */
/* ======================================================================== */

// Necessary by all custom allocators.
#include <stddef.h>
#include <new>
#include <stdexcept>
// Necessary for the Mallocator
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include "stdafx.h"

template <typename T>
class Mallocator
{
public:
  // Type defintions used by all allocators.
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using value_type = T;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  T* address(T& r) const;
  const T* address(const T& s) const;
  size_t max_size() const;

  template <typename U>
  struct rebind
  {
    using other = Mallocator<U>;
  };

  void construct(T* const p, const T& t) const;
  void destroy(T* const p) const;
  bool operator!=(const Mallocator& other) const;
  bool operator==(const Mallocator& other) const;
  
  Mallocator();
  Mallocator(const Mallocator&);
  
  template <typename U>
  Mallocator(const Mallocator<U>&);
  ~Mallocator();

  T* allocate(const size_t n) const;
  void deallocate(T* const p, const size_t n);

  template <typename U>
  T* allocate(const size_t n, const U* /* empty by design */) const;

private:
  Mallocator& operator=(const Mallocator&);
};

#include "Mallocator.tpp"

//! The type defintion for the mallocator string.
using MallocString = std::basic_string<char, std::char_traits<char>, Mallocator<char> >;

////////////////////////////////////////////////////////////////////////////////
#endif // Mallocator_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////