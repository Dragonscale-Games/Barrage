/* ======================================================================== */
/*!
 * \file            BehaviorNodeFactory.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Interface for allocating any type of behavior node via its name.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef BehaviorNodeFactory_BARRAGE_H
#define BehaviorNodeFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BehaviorNode.hpp"
#include "Utilities/Utilities.hpp"

namespace Barrage
{
  using BehaviorNodeFactoryMethod = BehaviorNodeDeepPtr(*)();
  using BehaviorNodeFactoryMethodMap = std::map<std::string, BehaviorNodeFactoryMethod>;

  //! Responsible for allocating new behavior nodes
  class BehaviorNodeFactory
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Tells the allocator how to allocate a behavior node of a
          given type.

        \tparam T
          The type of behavior node to register.

        \param name
          The name of the behavior node.
      */
      /**************************************************************/
      template <typename T>
      static void RegisterBehaviorNode(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Creates a behavior node whose type matches the given
          name. If no behavior node with that name has been registered,
          returns nullptr.

        \param name
          The name of the behavior node to create.

        \return
          Returns a pointer to the newly allocated behavior node if the
          behavior node has been registered, otherwise returns nullptr.
      */
      /**************************************************************/
      static BehaviorNodeDeepPtr CreateBehaviorNode(const std::string& name);

      /**************************************************************/
      /*!
        \brief
          Gets the list of all registered behavior nodes.

        \return
          Returns the list of all registered behavior nodes.
      */
      /**************************************************************/
      static const StringSet& GetBehaviorNodeNames();

    private:
      BehaviorNodeFactory() = delete;
      BehaviorNodeFactory(const BehaviorNodeFactory&) = delete;
      BehaviorNodeFactory& operator=(const BehaviorNodeFactory&) = delete;
      ~BehaviorNodeFactory() = delete;

      /**************************************************************/
      /*!
        \brief
          Creates a behavior node of the input type.

        \tparam T
          The type of behavior node to allocate.

        \return
          Returns a pointer to the newly allocated behavior node.
      */
      /**************************************************************/
      template <typename T>
      static BehaviorNodeDeepPtr AllocateBehaviorNode();

    private:
      static BehaviorNodeFactoryMethodMap behaviorNodeFactoryMethodMap_; //!< Maps names of behavior nodes to their allocation functions
      static StringSet behaviorNodeNames_;                               //!< Names of all registered behavior nodes
  };
}

#include "BehaviorNodeFactory.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // BehaviorNodeFactory_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////