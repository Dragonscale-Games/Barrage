/* ======================================================================== */
/*!
 * \file            Scene.cpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   A scene is a list of pools and game objects to spawn in a space.
 */
 /* ======================================================================== */

#include "Scene.hpp"

namespace Barrage
{
  Scene::Scene(const std::string& name) :
    name_(name),
    poolArchetypes_()
  {
  }

  Scene::Scene(const Scene& other) :
    name_(other.name_),
    poolArchetypes_()
  {
    CopyPoolArchetypes(other.poolArchetypes_);
  }

  Scene& Scene::operator=(const Scene& other)
  {
    name_ = other.name_;
    CopyPoolArchetypes(other.poolArchetypes_);

    return *this;
  }

  Scene::~Scene()
  {
    DeletePoolArchetypes();
  }

  const std::vector<PoolArchetype*>& Scene::GetPoolArchetypes()
  {
    return poolArchetypes_;
  }

  void Scene::AddPoolArchetype(PoolArchetype* archetype, unsigned* index)
  {
    if (index && poolArchetypes_.size() > *index)
    {
      poolArchetypes_.insert(poolArchetypes_.begin() + *index, archetype);
    }
    else
    {
      poolArchetypes_.push_back(archetype);
    }
  }

  void Scene::CopyPoolArchetypes(const std::vector<PoolArchetype*>& other)
  {
    DeletePoolArchetypes();

    for (auto it = other.begin(); it != other.end(); ++it)
    {
      poolArchetypes_.push_back(new PoolArchetype(**it));
    }
  }

  void Scene::DeletePoolArchetypes()
  {
    for (auto it = poolArchetypes_.begin(); it != poolArchetypes_.end(); ++it)
    {
      delete* it;
    }

    poolArchetypes_.clear();
  }
}