/* ======================================================================== */
/*!
 * \file            ComponentWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base component widget class. All component widgets should inherit from 
   this class.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentWidget_BARRAGE_H
#define ComponentWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Widget.hpp"
#include "Objects/Components/EngineComponents.hpp"

namespace Barrage
{
  //! Base component widget class
  class ComponentWidget : public Widget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~ComponentWidget() = default;

      /**************************************************************/
      /*!
        \brief
          This is where the widget's ImGui widget calls should be.
          Call this function between the GUI's StartWidgets and
          EndWidgets functions.
      */
      /**************************************************************/
      virtual void MakeWidget() = 0;

      /**************************************************************/
      /*!
        \brief
          Sets the component that this widget is editing.
      */
      /**************************************************************/
      virtual void SetComponent(Component* component) = 0;
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////