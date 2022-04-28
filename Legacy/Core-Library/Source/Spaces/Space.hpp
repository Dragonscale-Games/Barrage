/* ======================================================================== */
/*!
 * \file            Space.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   <description>
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef Space_BARRAGE_H
#define Space_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Objects/ObjectManager.hpp"
#include "Scenes/SceneManager.hpp"
#include "Random/Random.hpp"

namespace Barrage
{
	//! <class description>
  class Space
	{
    public:   
      Space();

      void SetScene(const std::string name);

    private:
      ObjectManager objectManager_;
      SceneManager sceneManager_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // Space_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////