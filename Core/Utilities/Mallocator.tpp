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

template <typename T>
T* Mallocator<T>::address(T& r) const
{
  return &r
}

template <typename T>
const T* Mallocator<T>::address(const T& s) const
{
  return &s
}

template <typename T>
size_t Mallocator<T>::max_size() const
{
  return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T);
}

template <typename T>
bool Mallocator<T>::operator!=(const Mallocator& other) const
{
  return !(*this == other);
}

template <typename T>
bool Mallocator<T>::operator==(const Mallocator& other) const
{
  return true;
}

template <typename T>
Mallocator<T>::Mallocator() {}
template <typename T>
Mallocator<T>::Mallocator(const Mallocator&) {}
template <typename T>
template <typename U>
Mallocator<T>::Mallocator(const Mallocator<U>&) {}
template <typename T>
Mallocator<T>::~Mallocator() {}

template <typename T>
T* Mallocator<T>::allocate(const size_t n) const
{
  // This is valid in new
  if (n == 0)
  {
    return NULL;
  }

  // Check for integer overflow.
  if (n > max_size())
  {
    throw std::bad_array_new_length();
  }

  // Really what we are doing here is wrapping around malloc.
  void* const pv = malloc(n * sizeof(T));
  if (pv == NULL)
  {
    throw std::bad_alloc();
  }

  return static_cast<T*>(pv);
}

template <typename T>
void Mallocator<T>::deallocate(T* const p, const size_t n)
{
  UNREFERENCED(n);
  free(p);
}

template <typename T>
template <typename U>
T* Mallocator<T>::allocate(const size_t n, const U* /* const hint */) const
{
  return allocate(n);
}

template <typename T>
void Mallocator<T>::construct(T* const p, const T& t) const
{
  void* const pv = static_cast<void*>(p);
  new (pv) T(t);
}

// Mitigate a compiler bug which tells the computer that p->~T() doesn't reference p.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#endif

template <typename T>
void Mallocator<T>::destroy(T* const p) const
{
  p->~T();
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
