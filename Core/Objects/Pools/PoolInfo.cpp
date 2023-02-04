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
  PoolInfo::PoolInfo(const std::string_view& poolName) :
    poolName_(poolName),
    objects_()
  {
  }
}