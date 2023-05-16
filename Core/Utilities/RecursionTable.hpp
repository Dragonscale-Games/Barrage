/* ======================================================================== */
/*!
 * \file            RecursionTable.hpp
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
     Provides an interface for a table commonly used in dynamic
     programming implementations of recursive algorithms.

 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef RecursionTable_BARRAGE_H
#define RecursionTable_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace Barrage
{
  //! Defines a utility class containing a triangular table, commonly
  //! found in recursive algorithms.
  template <typename T>
  class RecusionTable
  {
  public:
    //! Declares a forward declaration to a constant row in the table.
    class ConstRow;
    //! Declares a forward declaration to a row in the table.
    class Row;

  public:
    /**************************************************************/
    /*!
      \brief
        Creates a recursion table given a number of rows
        and a default element to fill the table with.
      \param rows
        The number of rows this table contains.
      \param defaultElem
        The default element to fill in the table with.
    */
    /**************************************************************/
    explicit RecursionTable(size_t rows = 0, const T& defaultElem = T(0));
    /**************************************************************/
    /*!
      \brief
        Gets the back element of the recursion table, commonly
        where the result of the recursive statement is written.
      \returns
        The last element of the last row in the recursive table.
    */
    /**************************************************************/
    const T& Back() const;
    /**************************************************************/
    /*!
      \brief
        Resizes the table to a specific number of rows.
      \param rows
        The new number of rows the table has after resizing.
    */
    /**************************************************************/
    void Resize(size_t rows, const T& defaultElem = T(0));
    /**************************************************************/
    /*!
      \brief
        Gets a single row in the recursion table.
      \param i
        The index into the table for a specific row.
      \returns
        A row at index i.
    */
    /**************************************************************/
    Row operator[](size_t i);
    /**************************************************************/
    /*!
      \brief
        Gets a single row in the recursive table.
      \param i
        The index into the table for a specific row.
      \returns
        A row at index i where it's elements are read-only.
    */
    /**************************************************************/
    ConstRow operator[](size_t i) const;

    /**************************************************************/
    /*!
      \returns
        The number of rows this table contains.
    */
    /**************************************************************/
    size_t GetRows() const;
    /**************************************************************/
    /*!
      \brief
        Gets the size of a given row.
      \param row
        The row to get the size of.
      \returns
        The size of the queried row.
    */
    /**************************************************************/
    size_t GetRowSize(size_t row) const;

  private:
    //! The number of rows this table contains.
    size_t rows_;
    //! The internal array for the table.
    std::vector<T> table_;

    /**************************************************************/
    /*!
      \brief
        Calculates the table's size in elements.
      \returns
        The table's size.
    */
    /**************************************************************/
    size_t GetTableSize() const;
    /**************************************************************/
    /*!
      \brief
        Gets the pointer offset to the beginning of the row
      \param row
        The row to query the pointer offset.
      \return
        The offset to the beginning of the row.
    */
    /**************************************************************/
    size_t GetRowOffset(size_t row) const;

  public:
    //! Defines a read-write row on this table.
    class Row
    {
    public:
      /**************************************************************/
      /*!
        \brief
          Defines a single row of the recursive table given
          a pointer to the start of the row and the number of 
          elements.
        \param rowPtr
          The pointer to the beginning of the table's row.
        \param elements
          The number of elements in the row.
      */
      /**************************************************************/
      Row(T* rowPtr, size_t elements);
      /**************************************************************/
      /*!
        \brief
          Gets a single writtable element in the row.
        \param i
          The index into the element gotten.
        \returns
          A reference to the element in the row.
      */
      /**************************************************************/
      T& operator[](size_t i);
      /**************************************************************/
      /*!
        \brief
          Gets a single read-only element in the row.
        \param i
          The index to the element gotten.
        \returns
          A constant reference to the element in the row.
      */
      /**************************************************************/
      const T& operator[](size_t i) const;

    private:
      //! The number of elements in the row.
      size_t elements_;
      //! The pointer to the beginning of a row.
      T* rowPtr_;
    };

    //! Defines a read-only row on this table.
    class ConstRow
    {
    public:
      /**************************************************************/
      /*!
        \brief
          Defines a single row of the recursive table given
          a pointer to the start of the row and the number of
          elements.
        \param rowPtr
          The pointer to the beginning of the table's row.
        \param elements
          The number of elements in the row.
      */
      /**************************************************************/
      ConstRow(T* rowPtr, size_t elements);
      /**************************************************************/
      /*!
        \brief
          Gets a single read-only element in the row.
        \param i
          The index to the element gotten.
        \returns
          A constant reference to the element in the row.
      */
      /**************************************************************/
      const T& operator[](size_t i) const;

    private:
      //! The number of elements in the row.
      size_t elements_;
      //! The pointer to the beginning of a row.
      T* rowPtr_;
    };
  };
}

#include "RecursionTable.tpp"
////////////////////////////////////////////////////////////////////////////////
#endif // RecursionTable_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////
