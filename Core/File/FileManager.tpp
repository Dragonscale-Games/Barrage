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

#include <utility>

namespace Barrage
{
  template <typename T>
  const T& FileManager::Load(const std::string& path, const std::string& filename) noexcept(false)
  {
    const std::string filepath = path + filename;
    if(cachedResources_.find(filepath) != cachedResources_.cend())
    {
        return *dynamic_cast<T*>(cachedResources_[filepath]);
    }
    else
    {
        T* resourceHandle = nullptr;
        {
            // First, attempt to create and load the resource.
            T resource(path, filename);
            resource.Load();
            // Then, if we succeeded, create a handle to a resource we can store
            // and do a std::move to that handle.
            resourceHandle = new T(std::move(resource));
        }
        // Cache the resource on a successful load.
        cachedResources_[filepath] = resourceHandle;
        return *resourceHandle;
    }
  }

  template <typename T>
  T& FileManager::Create(const std::string& path, const std::string& filename)
  {
    const std::string filepath = path + filename;
    if(cachedResources_.find(filepath) == cachedResources_.cend())
    {
      T* resource = new T(path, filename);
      cachedResources_[filepath] = resource;
      return *resource;
    }
    else
    {
      throw RuntimeError("Attempted to create a resource with the same filepath as an existing resource.");
    }
  }
}
