/* ======================================================================== */
/*!
 * \file            SystemManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   In charge of holding systems and calling their update functions.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SystemManager_BARRAGE_H
#define SystemManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "System.hpp"

namespace Barrage
{
  //! Maps system names to systems
  typedef std::map<std::string, std::shared_ptr<System>> SystemMap;

  //! Holds systems and calls their update functions
  class SystemManager
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.

        \param space
          The space the system manager lives in.
      */
      /**************************************************************/
      SystemManager(Space& space);

      /**************************************************************/
      /*!
        \brief
          Subscribes an object pool to each system that cares about
          it. If pool is nullptr, simply returns.
      */
      /**************************************************************/
      void Subscribe(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Unsubscribes an object pool from all systems.
      */
      /**************************************************************/
      void Unsubscribe(Pool* pool);

      /**************************************************************/
      /*!
        \brief
          Updates each system, carrying out system functions on all
          object pools subscribed to the systems.
      */
      /**************************************************************/
      void Update();

      /**************************************************************/
      /*!
        \brief
          Gets the system with the given name.

        \return
          Returns a pointer to the requested system, or nullptr if
          the system is not registered.
      */
      /**************************************************************/
      std::shared_ptr<System> GetSystem(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all active systems in the order that
          they're updating.

        \return
          Returns the list of all active systems in the order that
          they're updating.
      */
      /**************************************************************/
      const std::vector<std::string>& GetSystemUpdateOrder() const;

      /**************************************************************/
      /*!
        \brief
          Sets the order that the systems will be updated in. The user
          provides a list of system names, and systems will be updated
          in the order of the names on the list.

        \param updateOrderList
          An ordered list of system names.
      */
      /**************************************************************/
      void SetUpdateOrder(const std::vector<std::string>& updateOrderList);

    private:
      Space& space_;                             //!< The space the system manager lives in
      SystemMap systems_;                        //!< The collection of registered systems
      std::vector<std::string> updateOrderList_; //!< The order the systems will update in
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SystemManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////