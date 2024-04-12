/* ======================================================================== */
/*!
 * \file            PoolType.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A pool type is a combination of component names and tags. If a pool's
   components and tags match the pool type, it's considered to be that type.
*/
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolType_BARRAGE_H
#define PoolType_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Pool.hpp"

#include <string>
#include <vector>

namespace Barrage
{
  //! A combination of names and tags that define a pool type
  class PoolType
  {
  public:
    /**************************************************************/
    /*!
      \brief
        Default constructor.
    */
    /**************************************************************/
    PoolType();

    /**************************************************************/
    /*!
      \brief
        Adds a tag to the pool type.

      \param tag
        The tag to add.
    */
    /**************************************************************/
    void AddTag(const std::string& tag);

    /**************************************************************/
    /*!
      \brief
        Adds a component to the pool type.

      \param name
        The name of the C++ class used in the component. This
        should match the name passed to RegisterComponent<>();
    */
    /**************************************************************/
    void AddComponent(const std::string& name);

    /**************************************************************/
    /*!
      \brief
        Adds a component array to the pool type.

      \param name
        The name of the C++ class used in the component array. This
        should match the name passed to RegisterComponentArray<>();
    */
    /**************************************************************/
    void AddComponentArray(const std::string& name);

    /**************************************************************/
    /*!
      \brief
        Checks if a pool has at least the tags and components that
        correspond to the pool type.

      \param pool
        The pool to examine.

      \return
        Returns true if the pool has every component and tag named
        in the pool type.
    */
    /**************************************************************/
    bool MatchesPool(Pool* pool);

  private:
    std::vector<std::string> tags_;                //!< The tags of the pool type
    std::vector<std::string> componentNames_;      //!< The components of the pool type
    std::vector<std::string> componentArrayNames_; //!< The component arrays of the pool type
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolType_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////