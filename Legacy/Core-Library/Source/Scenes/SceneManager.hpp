/* ======================================================================== */
/*!
 * \file            SceneManager.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   Stores scenes and the object manager those scenes operate on. 
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef SceneManager_BARRAGE_H
#define SceneManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

#include "Scene.hpp"
#include "Objects/ObjectManager.hpp"

namespace Barrage
{
  //! Maps scene names to scenes
  typedef std::unordered_map<std::string, Scene*> SceneMap;
  
  //! <class description>
  class SceneManager
	{
    public:   
      SceneManager(ObjectManager& objectManager);

      ~SceneManager();

      void SetScene(const std::string& name) const;

      void LoadScene(const std::string& name);

      void SaveScene(const std::string& name) const;

    private:
      SceneMap scenes_;
      ObjectManager& objectManager_;
	};
}

////////////////////////////////////////////////////////////////////////////////
#endif // SceneManager_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////