/* ========================================================================= */
/*!
 *
 * \file            FileManager.tpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used for loading resources from disk and
 * a manager that caches them while providing utility functions 
 * to save/load them easier.

 * Implements the templated functions this module uses.
 */
/* ========================================================================= */

namespace Barrage
{
  template <typename T>
  const T& FileManager::Load(const std::string& path, const std::string& filename) noexcept(false)
  {
    T* resource = nullptr;
    // Load the resource before it crashes and dies.
    try
    {
      resource = Create(path, filename);
      resource->Load();
    }
    catch(RuntimeError& e)
    {
      delete resource;
      throw e;
    }

    // Cache the resource on a successful load.
    assert(cachedResources_.find(path + filename) == cachedResources.cend());
    cachedResources_[path + filename] = resource;
    return *resource;
  }

  template <typename T>
  T& FileManager::Create(const std::string& path, const std::string& filename)
  {
    return new T(path, filename);
  }
}
