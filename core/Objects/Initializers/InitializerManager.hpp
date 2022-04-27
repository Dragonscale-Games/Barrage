/* ======================================================================== */
/*!
 * \file            InitializerManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
    Keeps track of object initialization functions and their names.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef InitializerManager_BARRAGE_H
#define InitializerManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/Pools/Pool.hpp"

#include <unordered_map>

namespace Barrage
{
  // An initializer is a function that modifies a new object's fields
  // Arguments: initializer pool, pool to modify, index of first new object, number of new objects 
  typedef void (*Initializer)(Pool&, Pool&, unsigned, unsigned);
  
  //! Maps system names to systems
  typedef std::unordered_map<std::string, Initializer> InitializerMap;
  
  //! An ordered list of initializer names
  typedef std::vector<std::string> InitializerList;

  //! Keeps track of object initialization functions and their names
  class InitializerManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      InitializerManager();

      /**************************************************************/
      /*!
        \brief
          Adds an initializer to the manager's collection.

        \param name
          The name the user would like assigned to the initializer.

        \param initializer
          The initializer to add.
      */
      /**************************************************************/
      void RegisterInitializer(const std::string name, Initializer initializer);

      /**************************************************************/
      /*!
        \brief
          Gets an initializer function (if it was registered).

        \param name
          The name of an initializer.

        \return
          Returns the initializer with the given name, or nullptr if
          it doesn't exist.
      */
      /**************************************************************/
      Initializer GetInitializer(const std::string name);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered initializers.

        \return
          Returns the list of all registered initializers.
      */
      /**************************************************************/
      InitializerList GetInitializerNames();

    private:
      InitializerMap initializers_;      //!< The collection of registered initializers
      InitializerList initializerNames_; //!< The names of all registered initializers
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // InitializerManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////