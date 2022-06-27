/* ======================================================================== */
/*!
 * \file            SpriteWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Sprite components.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpriteWidget_BARRAGE_H
#define SpriteWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Components/ComponentWidget.hpp"

namespace Barrage
{
  //! widget for editing Sprite components
  class SpriteWidget : public ComponentWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      SpriteWidget();

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
      Sprite* spriteComponent_; //!< the component this widget is editing
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpriteWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////