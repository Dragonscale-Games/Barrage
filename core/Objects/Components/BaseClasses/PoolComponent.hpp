/* ======================================================================== */
/*!
 * \file            PoolComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base pool component class that all pool components should inherit from.
   A pool component is a component that is unique per object pool that
   contains it.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef PoolComponent_BARRAGE_H
#define PoolComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseComponent.hpp"

namespace Barrage
{
	//! Base pool component class that all pool components should inherit from
  class PoolComponent : public Component
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~PoolComponent() = default;

      /**************************************************************/
      /*!
        \brief
          Tells user this is a pool component type.

        \return
          Returns pool component type to identify component.
      */
      /**************************************************************/
      virtual Component::Type GetType() override;
  };

  //! Maps pool component names to pool component singletons
  typedef std::unordered_map<std::string, PoolComponent*> PoolComponentMap;

  //! Contains a list of names of pool components
  typedef std::vector<std::string> PoolComponentList;
}

////////////////////////////////////////////////////////////////////////////////
#endif // PoolComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////