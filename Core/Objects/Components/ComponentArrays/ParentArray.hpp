/* ======================================================================== */
/*!
 * \file            ParentArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Game objects use this component if another game object is their parent. 
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ParentArray_BARRAGE_H
#define ParentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"
#include "../SharedComponents/ObjectDirectory.hpp"

namespace Barrage
{
  //!< Keeps track of a game object's parent
  struct Parent
  {
    Pool* pool_;                  //!< the pool where the parent object lives
    ObjectHandle* handle_;        //!< the handle of the parent object within that pool
    unsigned long long parentId_; //!< the id of the parent object (should be checked against the id in the handle)

    inline Parent() : pool_(nullptr), handle_(nullptr), parentId_(INVALID_ID){}
  };

  typedef ComponentArrayT<Parent> ParentArray;

  template <>
  inline std::string ParentArray::GetClassName() { return "ParentArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // ParentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////