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

#include "Objects/Components/BaseClasses/SharedComponent.hpp"
#include "Objects/Components/BaseClasses/ComponentArray.hpp"

#include <unordered_set>

namespace Barrage
{
  typedef std::unordered_set<std::string> TagSet;
  
  //! Container for a prespecified number of objects
  class Pool
  {
    public:  
      // default constructor is private below - only a pool manager should construct pools
      
      Pool(const Pool& other) = delete;

      Pool& operator=(const Pool& rhs) = delete;
      
      /**************************************************************/
      /*!
        \brief
          Deallocates all components attached to the pool.
      */
      /**************************************************************/
      ~Pool();

      /**************************************************************/
      /*!
        \brief
          Determines if a pool has a given tag.

        \param tag
          The tag to check for.

        \return
          Returns true if the pool has the tag, returns false
          otherwise.
      */
      /**************************************************************/
      bool HasTag(const std::string& tag) const;

      /**************************************************************/
      /*!
        \brief
          Get a reference to a given component array. Throws an
          out_of_range exception if no component array matches the
          input name.

        \tparam T
          The type of component array to get.

        \param componentName
          The name of the component array to get.

        \return
          Returns a reference to the component array with the given
          name.
      */
      /**************************************************************/
      template <typename T>
      T* GetComponentArray(const std::string& componentName);

      /**************************************************************/
      /*!
        \brief
          Get a reference to a given shared component. Throws an
          out_of_range exception if no shared component matches the
          input name.

        \tparam T
          The type of shared component to get.

        \param componentName
          The name of the shared component to get.

        \return
          Returns a reference to the shared component with the given
          name.
      */
      /**************************************************************/
      template <typename T>
      T* GetSharedComponent(const std::string& componentName);

    public:
      TagSet tags_;                         //!< Holds the pool's tags
      ComponentArrayMap componentArrays_;   //!< Holds component arrays and their names
      SharedComponentMap sharedComponents_; //!< Holds shared components and their names
      unsigned size_;                       //!< Number of currently active objects
      const unsigned capacity_;             //!< Total number of objects the pool can hold

    private:
      /**************************************************************/
      /*!
        \brief
          Initializes the capacity of an object pool. Components are
          added by a pool manager, not by this function.

        \param
          The number of objects the pool will be able to hold.
      */
      /**************************************************************/
      Pool(unsigned capacity);

    friend class PoolManager;
  };
}

#include "Pool.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Pool_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////