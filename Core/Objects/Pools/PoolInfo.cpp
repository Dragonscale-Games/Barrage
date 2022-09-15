/* ======================================================================== */
/*!
 * \file            PoolInfo.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Contains all the info the object manager needs to create a pool and
   populate it with objects.
*/
/* ======================================================================== */

#include "PoolInfo.hpp"

namespace Barrage
{
  PoolInfo::PoolInfo(const std::string& poolName, const std::string& archetypeName, unsigned capacity) :
    poolName_(poolName),
    archetypeName_(archetypeName),
    capacity_(capacity),
    objects_()
  {
  }
}