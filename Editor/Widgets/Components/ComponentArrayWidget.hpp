/* ======================================================================== */
/*!
 * \file            ComponentArrayWidget.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Allows user to edit the values of a component array.
 */
 /* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef ComponentArrayWidget_BARRAGE_H
#define ComponentArrayWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include <imgui/imgui.h>
#include <Objects/Components/ComponentArray.hpp>
#include <string>

namespace Barrage
{
  //! Allows user to edit the values of a component array
  class ComponentArrayWidget
  {
    public:
      /**************************************************************/
      /*!
        \brief
          Adds a widget to the window that allows the user to edit
          a component array.
         
        \param componentName
          The name of the component array.

        \param componentArray
          The component array being edited.

        \return
          Returns true if the component array's value changed, returns 
          false otherwise.
      */
      /**************************************************************/
      static void Use(const std::string& componentName, DeepPtr<ComponentArray>& componentArray);
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // ComponentArrayWidget_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////