/* ======================================================================== */
/*!
 * \file            HandleIndexArray.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   The HandleIndex component, together with the HandleDirectory component, allows
   specific game objects to be located inside a pool.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef HandleIndexArray_BARRAGE_H
#define HandleIndexArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "../BaseClasses/ComponentArray.hpp"

#include <climits>

namespace Barrage
{
    static const unsigned NO_HANDLE = UINT_MAX;
    
    //!< An object's index in the HandleDirectory
    struct HandleIndex
    {
        unsigned index_; //!< An object's index in the HandleDirectory

        inline HandleIndex() : index_(NO_HANDLE) {}
    };

    typedef ComponentArrayT<HandleIndex> HandleIndexArray;

    template <>
    inline std::string HandleIndexArray::GetClassName() { return "HandleIndexArray"; }
}

////////////////////////////////////////////////////////////////////////////////
#endif // HandleIndexArray_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////