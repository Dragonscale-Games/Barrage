/* ======================================================================== */
/*!
 * \file            Pool.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   An object pool is a block of memory that can hold a prespecified number
   of objects with a specific combination of components.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef Pool_BARRAGE_H
#define Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/EngineComponents.hpp"

#include <iostream>

namespace Barrage
{
  //! Container for a prespecified number of objects
  class Pool
  {
    public:  
      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to the pool.
      */
      /**************************************************************/
      ~Pool();

    public:
      ObjectComponentMap objectComponents_; //!< Holds object component arrays and maps names to the arrays
      PoolComponentMap poolComponents_;     //!< Holds pool components and maps names to them
      unsigned activeObjects_;              //!< Number of currently active objects
      const unsigned capacity_;             //!< Total number of objects the pool can hold

    private:
      /**************************************************************/
      /*!
        \brief
          Initializes the capacity of an object pool. Components are
          added by a pool manager, not by this function.
      */
      /**************************************************************/
      Pool(unsigned capacity);

      friend class PoolManager;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////