/* ======================================================================== */
/*!
 * \file            HandleDirectory.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The HandleDirectory component, together with the HandleIndex component, 
   allows specific game objects to be located inside a pool.

   The HandleDirectory keeps track of the pool index of each game object.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef HandleDirectory_BARRAGE_H
#define HandleDirectory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/SharedComponent.hpp"
#include "../ComponentArrays/HandleIndexArray.hpp"

#include <vector>

namespace Barrage
{
  static const unsigned long long DEAD_OBJECT_ID = ULLONG_MAX;
  
  struct Handle
  {
    unsigned long long id_;
    unsigned poolIndex_;
  };
  
  //! Tells which index corresponds to a specific object at any given time
  class HandleDirectory : public SharedComponent
  {
    public:
      inline HandleDirectory() : handles_(), freeList_(), currentId_(0) {}

      inline std::string GetClassName() override { return "HandleDirectory"; }

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

          Handle new_handle;

          new_handle.poolIndex_ = poolIndex;
          new_handle.id_ = currentId_++;
          
          handles_.push_back(new_handle);
        }

        return handle_index;
      }

      inline Handle& GetHandle(unsigned handleIndex)
      {
        return handles_[handleIndex];
      }

      inline void FreeHandle(unsigned handleIndex)
      {
        freeList_.push_back(handleIndex);
        handles_[handleIndex].id_ = DEAD_OBJECT_ID;
      }

    public:
      std::vector<Handle> handles_;
      std::vector<unsigned> freeList_;
      unsigned long long currentId_;

  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // Addresser_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////