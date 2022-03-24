/* ======================================================================== */
/*!
 * \file            TagsWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Tags components.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef TagsWidget_BARRAGE_H
#define TagsWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Components/ComponentWidget.hpp"

namespace Barrage
{
  //! widget for editing Tags components
  class TagsWidget : public ComponentWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      TagsWidget();

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
      Tags* tagsComponent_; //!< the component this widget is editing
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // TagsWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////