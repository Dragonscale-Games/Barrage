/* ======================================================================== */
/*!
 * \file            DirectoryIndexArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The DirectoryIndex component, together with the ObjectDirectory component, 
   allows specific game objects to be located inside a pool.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef DirectoryIndexArray_BARRAGE_H
#define DirectoryIndexArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"

#include <climits>

namespace Barrage
{
    static const unsigned NO_HANDLE = UINT_MAX;
    
    //!< An object's index in the ObjectDirectory
    struct DirectoryIndex
    {
        unsigned index_; //!< An object's index in the HandleDirectory

        inline DirectoryIndex() : index_(NO_HANDLE) {}
    };

    typedef ComponentArrayT<DirectoryIndex> DirectoryIndexArray;

    template <>
    inline std::string DirectoryIndexArray::GetClassName() { return "DirectoryIndexArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // DirectoryIndexArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////