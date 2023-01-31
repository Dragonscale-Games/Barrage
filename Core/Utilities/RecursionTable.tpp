/* ======================================================================== */
/*!
 * \file            RecursionTable.tpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
     Provides an interface for a table commonly used in dynamic
     programming implementations of recursive algorithms.

 */
 /* ======================================================================== */

#include <algorithm>
#include <cassert>

namespace Barrage
{
  template <typename T>
  RecursionTable<T>::RecursionTable(size_t rows, const T& defaultElem)
  {
    Resize(rows, defaultElem);
  }

  template <typename T>
  const T& RecursionTable<T>::Back() const
  {
    return table_.back();
  }

  template <typename T>
  RecursionTable<T>::Resize(size_t rows, const T& defaultElem)
  {
    rows_ = rows;
    table_.resize(GetTableSize(), defaultElem);
  }

  template <typename T>
  typename RecursionTable<T>::Row RecursionTable<T>::operator[](size_t i)
  {
    assert(i < GetTableSize());
    return Row(table_.data() + GetRowOffset(i), GetRowSize(i));
  }

  template <typename T>
  typename RecursionTable<T>::ConstRow RecursionTable<T>::operator[](size_t i) const
  {
    assert(i < GetTableSize());
    return ConstRow(table_.data() + GetRowOffset(i), GetRowSize(i));
  }

  template <typename T>
  size_t RecursionTable<T>::GetRows() const
  {
    return rows_;
  }

  template <typename T>
  size_t RecursionTable<T>::GetRowSize(size_t row) const
  {
    assert(_rows - row > 0);
    return _rows - row;
  }

  template <typename T>
  size_t RecursionTable<T>::GetTableSize() const
  {
    return _rows * (_rows + 1) / 2u;
  }

  template <typename T>
  size_t RecursionTable<T>::GetRowOffset(size_t row) const
  {
    assert(row < rows_);
    // Get the number of elements in table.
    size_t tableSize = GetTableSize();
    // Offset from the end.
    size_t offsetFromEnd = row * (row + 1) / 2u;
    // Return n elements from the back of the table.
    return tableSize - offsetFromEnd;
  }

  template <typename T>
  RecursionTable<T>::Row::Row(T* rowPtr, size_t elements) : elements_(elements), rowPtr_(rowPtr)
  {
    assert(rowPtr != nullptr);
  }

  template <typename T>
  T& RecursionTable<T>::Row::operator[](size_t i)
  {
    assert(i < elements_);
    return rowPtr_[i];
  }

  template <typename T>
  const T& RecursionTable<T>::Row::operator[](size_t i) const
  {
    assert(i < elements_);
    return rowPtr_[i];
  }

  template <typename T>
  RecursionTable<T>::ConstRow::ConstRow(T* rowPtr, size_t elements) : elements_(elements), rowPtr_(rowPtr)
  {
    assert(rowPtr != nullptr);
  }

  template <typename T>
  const T& RecursionTable<T>::ConstRow::operator[](size_t i) const
  {
    assert(i < elements_);
    return rowPtr_[i];
  }
}
