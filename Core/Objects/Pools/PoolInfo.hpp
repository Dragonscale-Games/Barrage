/* ======================================================================== */
/*!
 * \file            PoolInfo.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Contains all the info the object manager needs to create a pool and 
   populate it with objects.
*/
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolInfo_BARRAGE_H
#define PoolInfo_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

namespace Barrage
{
  //! contains all information needed to create a pool and populate it with objects
  struct PoolInfo
  {
    public:
      PoolInfo(const std::string_view& poolName, const std::string_view& archetypeName, unsigned capacity = 1);

    public:
      const std::string_view poolName_;       //!< Name that will be assigned to the pool
      const std::string_view archetypeName_;  //!< Name of the archetype used to construct the pool
      const unsigned capacity_;               //!< Number of objects the pool can hold
      std::vector<std::string_view> objects_; //!< Names of object archetypes used to construct starting objects
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolInfo_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////