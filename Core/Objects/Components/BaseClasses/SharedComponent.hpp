/* ======================================================================== */
/*!
 * \file            SharedComponent.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base shared component class that all shared components should inherit from.
   A shared component is a component that all objects in a pool use. 
   For instance, all objects in a pool may use the same sprite component.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SharedComponent_BARRAGE_H
#define SharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseComponent.hpp"

namespace Barrage
{
	//! Base shared component class that all shared components should inherit from
  class SharedComponent : public Component
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~SharedComponent() = default;

      /**************************************************************/
      /*!
        \brief
          Used to identify this object as a shared component.

        \return
          Returns the "SHARED" component type.
      */
      /**************************************************************/
      virtual Component::Type GetType() override;
  };

  //! Associates each shared component with its name
  typedef std::unordered_map<std::string, SharedComponent*> SharedComponentMap;
}

////////////////////////////////////////////////////////////////////////////////
#endif // SharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////