/* ======================================================================== */
/*!
 * \file            SystemFactory.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of registered system via its name.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SystemFactory_BARRAGE_H
#define SystemFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "System.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  using SystemFactoryMethod = std::shared_ptr<System>(*)(Space&);
  using SystemFactoryMethodMap = std::map<std::string, SystemFactoryMethod>;

  //! Responsible for allocating systems
  class SystemFactory
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Tells the allocator how to allocate a system of a
          given type.

        \tparam T
          The type of system to register.

        \param name
          The name of the system.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterSystem(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Creates a system whose type matches the given
          name. If no system with that name has been registered,
          returns nullptr.

        \param name
          The name of the system to create.

        \param space
          The space the system will live in.

        \return
          Returns a pointer to the newly allocated system if the
          system has been registered, otherwise returns nullptr.
      */
      /**************************************************************/
      static std::shared_ptr<System> CreateSystem(const std::string& name, Space& space);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered systems.

        \return
          Returns the list of all registered systems.
      */
      /**************************************************************/
      static const StringSet& GetSystemNames();

    private:
      SystemFactory() = delete;
      SystemFactory(const SystemFactory&) = delete;
      SystemFactory& operator=(const SystemFactory&) = delete;
      ~SystemFactory() = delete;

      /**************************************************************/
      /*!
        \brief
          Creates a system of the input type.

        \tparam T
          The type of system to allocate.

        \return
          Returns a shared pointer to the newly allocated system.
      */
      /**************************************************************/
      template <typename T>
      static std::shared_ptr<System> AllocateSystem(Space& space);

    private:
      static SystemFactoryMethodMap systemFactoryMethodMap_; //!< Maps names of systems to their allocation functions
      static StringSet systemNames_;                         //!< Names of all registered systems
  };
}

#include "SystemFactory.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // SystemFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////