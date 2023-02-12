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
      PoolInfo(const std::string& poolName);

    public:
      std::string poolName_;             //!< Name of the archetype used to construct the pool
      std::vector<std::string> objects_; //!< Names of object archetypes used to construct starting objects
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolInfo_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////