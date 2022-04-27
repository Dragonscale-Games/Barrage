/* ======================================================================== */
/*!
 * \file            SystemManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <put description here> 
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SystemManager_BARRAGE_H
#define SystemManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseSystem.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace Barrage
{
  //! Maps system names to systems
  typedef std::unordered_map<std::string, System*> SystemMap;

  //! <class description>
  class SystemManager
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      SystemManager();

      /**************************************************************/
      /*!
        \brief
          Deletes all systems registered to the system manager.
      */
      /**************************************************************/
      ~SystemManager();

      /**************************************************************/
      /*!
        \brief
          Instantiates a system and adds it to the system manager's
          collection of systems (the system map). Also appends the
          system's name to the update order list.

        \tparam T
          The type of the system to register.

        \param systemName
          The name the user would like to be assigned to the system.
      */
      /**************************************************************/
      template <typename T>
      void RegisterSystem(const std::string& systemName);

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
          Gets the list of all registered systems.

        \return
          Returns the list of all registered systems.
      */
      /**************************************************************/
      std::vector<std::string> GetRegisteredSystemNames();

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
      std::vector<std::string> GetSystemUpdateOrder();

    private:
      SystemMap systems_;                        //!< The collection of registered systems
      std::vector<std::string> systemNames_;     //!< The names of all registered systems
      std::vector<std::string> updateOrderList_; //!< The order the systems will update in

    friend class ObjectManager;
	};
}

#include "SystemManager.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // SystemManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////