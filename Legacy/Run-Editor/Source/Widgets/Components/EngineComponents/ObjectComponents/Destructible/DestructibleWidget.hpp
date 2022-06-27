/* ======================================================================== */
/*!
 * \file            DestructibleWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Destructible components.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef DestructibleWidget_BARRAGE_H
#define DestructibleWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Components/ComponentWidget.hpp"

namespace Barrage
{
  //! widget for editing Destructible components
  class DestructibleWidget : public ComponentWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      DestructibleWidget();

      /**************************************************************/
      /*!
        \brief
          This is where the widget's ImGui widget calls should be.
          Call this function between the GUI's StartWidgets and
          EndWidgets functions.
      */
      /**************************************************************/
      void MakeWidget();

      /**************************************************************/
      /*!
        \brief
          Sets the component that this widget is editing.

        \param component
          The component that this widget is editing.
      */
      /**************************************************************/
      void SetComponent(Component* component);

    private:
      Destructible* destructibleComponent_; //!< the component this widget is editing
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // DestructibleWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////