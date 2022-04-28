/* ======================================================================== */
/*!
 * \file            Widget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Base widget class. All widgets should inherit from this class.
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Widget_BARRAGE_H
#define Widget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
	//! Base widget class
  class Widget
	{
    public:   
      /**************************************************************/
      /*!
        \brief
          Base class requires virtual destructor.
      */
      /**************************************************************/
      virtual ~Widget() = default;

      /**************************************************************/
      /*!
        \brief
          This is where the widget's ImGui widget calls should be.
          Call this function between the GUI's StartWidgets and
          EndWidgets functions.
      */
      /**************************************************************/
      virtual void MakeWidget() = 0;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Widget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////