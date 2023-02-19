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

#include <rttr/rttr_enable.h>

namespace Barrage
{
	//! Base shared component class that all shared components should inherit from
  class SharedComponent
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
          Copies another component to this component. They must be
          the same type.

        \param other
          The component to copy.
      */
      /**************************************************************/
      virtual void CopyToThis(const SharedComponent& other) = 0;

      // Notify rttr of the component hierarchy.
      RTTR_ENABLE()
  };

  //! All shared components are a specialization of this template
  template <typename T>
  class SharedComponentT : public SharedComponent
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Constructs component.
      */
      /**************************************************************/
      SharedComponentT();

      /**************************************************************/
      /*!
        \brief
          Copies another component to this component. They must be
          the same type.

        \param other
          The component to copy.
      */
      /**************************************************************/
      void CopyToThis(const SharedComponent& other) override;

      /**************************************************************/
      /*!
        \brief
          Accesses the underlying component data.

        \return
          Returns a reference to the component data.
      */
      /**************************************************************/
      T& Data();

    public:
      T data_;

      RTTR_ENABLE(SharedComponent)
  };

  //! Associates each shared component with its name
  typedef std::unordered_map<std::string_view, SharedComponent*> SharedComponentMap;
}

#include "SharedComponent.tpp"

////////////////////////////////////////////////////////////////////////////////
#endif // SharedComponent_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////