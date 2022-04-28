/* ======================================================================== */
/*!
 * \file            SpawnerWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Widget for editing Spawner components.
 */
 /* ======================================================================== */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef SpawnerWidget_BARRAGE_H
#define SpawnerWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Widgets/Components/ComponentWidget.hpp"

namespace Barrage
{
  //! widget for editing Spawner components
  class SpawnerWidget : public ComponentWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Default constructor.
      */
      /**************************************************************/
      SpawnerWidget();

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
      Spawner* spawnerComponent_; //!< the component this widget is editing
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // SpawnerWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////