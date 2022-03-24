/* ======================================================================== */
/*!
 * \file            RotationWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Rotation components.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef RotationWidget_BARRAGE_H
#define RotationWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Components/ComponentWidget.hpp"

namespace Barrage
{
  //! widget for editing Rotation components
  class RotationWidget : public ComponentWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      RotationWidget();

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
      Rotation* rotationComponent_; //!< the component this widget is editing
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // RotationWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////