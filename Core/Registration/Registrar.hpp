/* ======================================================================== */
/*!
 * \file            Registrar.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Handles registration for gameplay code.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Registrar_BARRAGE_H
#define Registrar_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

namespace Barrage
{
  //! Manages all existing spaces and allows creation of new spaces
  class Registrar
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Function defined in the (external) Gameplay library that
          registers all gameplay code.
      */
      /**************************************************************/
      static void Registration();

      static std::vector<std::string>& GetSystemUpdateOrder();

    private:
      Registrar() = delete;
      Registrar(const Registrar&) = delete;
      Registrar& operator=(const Registrar&) = delete;
      ~Registrar() = delete;

      /**************************************************************/
      /*!
        \brief
          Registers a component for use in the engine.

        \tparam T
          The type of data the component will wrap.

        \param componentName
          The name of the component's C++ class.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterComponent(const std::string& componentName);

      /**************************************************************/
      /*!
        \brief
          Registers a component array for use in the engine.

        \tparam T
          The type of component the array will contain.

        \param componentName
          The name of the component's C++ class.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterComponentArray(const std::string& componentName);

      /**************************************************************/
      /*!
        \brief
          Registers a spawn rule for use in the engine.

        \tparam T
          The type of spawn rule to register.

        \param name
          The name of the spawn rule.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterSpawnRule(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Registers a gameplay system for use in the engine.

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
          Registers a tag for use in the engine.

        \param tag
          The tag to register.
      */
      /**************************************************************/
      static void RegisterTag(const std::string& tag);

      /**************************************************************/
      /*!
        \brief
          Function defined in the (external) Gameplay library that
          sets the order in which gameplay systems update.

        \param updateOrder
          The order in which the systems should update. A system may
          be included more than once.
      */
      /**************************************************************/
      static void SetSystemUpdateOrder(const std::vector<std::string>& updateOrder);

    private:
      static std::vector<std::string> systemUpdateOrder_;
  };
}

#include "Registrar.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // Registrar_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////