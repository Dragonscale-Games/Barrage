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
#include "../Components/ObjectDirectory.hpp"

namespace Barrage
{
  //!< Keeps track of a game object's parent
  struct Parent
  {
    Pool* pool_;                  //!< the pool where the parent object lives
    ObjectHandle* handle_;        //!< the handle of the parent object within that pool
    unsigned long long parentId_; //!< the original id of the parent object (used to check if parent still exists)

    inline Parent() : pool_(nullptr), handle_(nullptr), parentId_(INVALID_ID){}

    inline bool Exists()
    {
      return handle_->id_ == parentId_;
    }
  };

  typedef ComponentArrayT<Parent> ParentArray;
}

////////////////////////////////////////////////////////////////////////////////
#endif // ParentArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////