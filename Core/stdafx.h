/* ======================================================================== */
/*!
 * \file            stdafx.h
 * \par             Barrage Engine
 * \author          David Wong Cascante
 * \par             david.wongcascante\@gmail.com

 * \brief
 * All common code and includes to be included by all files.
 */
/* ======================================================================== */

#include <cassert>
#include <csignal>

/****************************************************************************/
/*!
  \brief
    A macro that helps users get the return address of the current
    function.
*/
/****************************************************************************/
#ifdef _MSC_VER
#if defined(__clang__) || defined(__GNUC__)
#define RETURN_ADDRESS() __builtin_return_address(0)
#else
#include <intrin.h>
#define RETURN_ADDRESS() _ReturnAddress()
#endif
#else
#define RETURN_ADDRESS() __builtin_return_address(0)
#endif

/****************************************************************************/
/*!
  \brief
    Defines a variable/paramater as unreferenced for the compiler.
  \param x
    The variable/parameter as unreferenced.
*/
/****************************************************************************/
#define UNREFERENCED(x) (void)x
/****************************************************************************/
/*!
  \brief
    Breaks execution of the program, useful for debugging.
*/
/****************************************************************************/
#ifdef _WIN32
#define BREAKPOINT() __debugbreak()
#else
#define BREAKPOINT() std::raise(SIGINT)
#endif
/****************************************************************************/
/*!
  \brief
    Defines a macro to let users know when a function is not ready
    to be used yet.
*/
/****************************************************************************/
#define NO_IMPL() BREAKPOINT()

/****************************************************************************/
/*!
  \brief
    Defines a macro to let users know when a function really shouldn't
    be used anymore.
*/
/****************************************************************************/
#define DEPRECATED() NO_IMPL()

/****************************************************************************/
/*!
  \brief
    Makes calling pointers to member functions trivial.

  \param object
    The object to invoke the function on.

  \param memberFuncPtr
    The pointer to a member function defined for the object above.
*/
/****************************************************************************/
#define CALL_MEMBER_FN(object, memberFuncPtr) ((object).*(memberFuncPtr))
