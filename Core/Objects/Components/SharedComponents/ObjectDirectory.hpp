/* ======================================================================== */
/*!
 * \file            ObjectDirectory.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The ObjectDirectory component, together with the DirectoryIndex component, 
   allows specific game objects to be located inside a pool.

   The ObjectDirectory keeps track of the pool index of each game object.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectDirectory_BARRAGE_H
#define ObjectDirectory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/SharedComponent.hpp"
#include "../ComponentArrays/DirectoryIndexArray.hpp"
#include "../../Pools/Pool.hpp"

#include <vector>

namespace Barrage
{
  static const unsigned long long DEAD_OBJECT_ID = ULLONG_MAX;
  static const unsigned long long INVALID_ID = ULLONG_MAX - 1;

  struct ObjectHandle
  {
    unsigned long long id_;
    unsigned poolIndex_;
  };
  
  //! Tells which index corresponds to a specific object at any given time
  class ObjectDirectory : public SharedComponent
  {
    public:
      inline ObjectDirectory() : handles_(), freeList_(), currentId_(0) {}

      inline unsigned CreateHandle(unsigned poolIndex)
      {
        unsigned handle_index = NO_HANDLE;
        
        if (!freeList_.empty())
        {
          handle_index = freeList_.back();
          freeList_.pop_back();
          handles_[handle_index].poolIndex_ = poolIndex;
          handles_[handle_index].id_ = currentId_++;
        }
        else
        {
          handle_index = static_cast<unsigned>(handles_.size());

          ObjectHandle new_handle;

          new_handle.poolIndex_ = poolIndex;
          new_handle.id_ = currentId_++;
          
          handles_.push_back(new_handle);
        }

        return handle_index;
      }

      inline ObjectHandle& GetHandle(unsigned directoryIndex)
      {
        return handles_[directoryIndex];
      }

      inline void FreeHandle(unsigned directoryIndex)
      {
        freeList_.push_back(directoryIndex);
        handles_[directoryIndex].id_ = DEAD_OBJECT_ID;
      }

    private:
      std::vector<ObjectHandle> handles_;
      std::vector<unsigned> freeList_;
      unsigned long long currentId_;

  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ObjectDirectory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////