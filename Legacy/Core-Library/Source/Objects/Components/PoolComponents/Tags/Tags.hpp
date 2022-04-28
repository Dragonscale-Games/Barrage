/* ======================================================================== */
/*!
 * \file            Tags.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 

 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Tags_BARRAGE_H
#define Tags_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Components/BaseClasses/PoolComponent.hpp"

#include <unordered_set>

namespace Barrage
{
  typedef std::unordered_set<std::string> TagSet;
  
  //! An optional collection of strings that identify an object pool.
  class Tags : public PoolComponent
  {
  public:
    /**************************************************************/
    /*!
      \brief
        An optional collection of strings that identify an object
        pool. For example, an object pool may have a "Player" tag,
        or a "Bullet" tag and a "Hostile" tag.

        Tags for a pool should not change once initialized.
    */
    /**************************************************************/
    Tags();

    /**************************************************************/
    /*!
      \brief
        Helper function that determines if a pool has a given tag.

      \param tag
        The tag to check for.

      \return
        Returns true if the pool has the given tag and returns
        false otherwise.
    */
    /**************************************************************/
    bool HasTag(const std::string& tag) const;

  public:
    TagSet tagSet_; //!< Holds the tags that belong to the object
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Tags_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////