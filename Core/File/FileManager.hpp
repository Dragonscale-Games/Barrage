/* ========================================================================= */
/*!
 *
 * \file            FileManager.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface used for loading resources from disk and
 * a manager that caches them while providing utility functions 
 * to save/load them easier.
 */
/* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef FileManager_MODULE_H
#define FileManager_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <string>
#include <string_view>
#include <map>
#include <Utilities/RuntimeError.hpp>

namespace Barrage
{
  //! The interface for the resource type.
  class FileResource
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Defines a default constructor when a suer
    */
    /*************************************************************************/
    FileResource() noexcept;
    /*************************************************************************/
    /*!
      \brief
        A move constructor for file resources. Used when loading
        resources in the manager.
      \param other
        The resource being moved over to this instance.
    */
    /*************************************************************************/
    FileResource(FileResource&& other) noexcept;
    /*************************************************************************/
    /*!
      \brief
        Creates a resource using a given path and filename.
      \param path
        The path to find the file.
      \param filename
        The name of the file being loaded.
    */
    /*************************************************************************/
    FileResource(const std::string_view& path, const std::string_view& filename) noexcept;
    /*************************************************************************/
    /*!
      \brief
        A defined copy constructor for resources.
      \param original
        The original resource to copy over.
    */
    /*************************************************************************/
    FileResource(const FileResource& original);
    /*************************************************************************/
    /*!
      \brief
        Define a virtual destructor for resources so they get deleted
        appropriately.
        This function cannot throw because we are using RAII semantics
        for exception-safe code.
    */
    /*************************************************************************/
    virtual ~FileResource() noexcept = default;
    /*************************************************************************/
    /*!
      \brief
        Loads a resource using the saved path and filename.
      \throws Barrage::RuntimeError
        If we failed to load the resource at the given file name and path.
    */
    /*************************************************************************/
    void Load() noexcept(false);
    /*************************************************************************/
    /*!
      \brief
        Saves this resource to disk at the specified path with the name
        given to it.
      \throws Barrage::RuntimeError
        If this failed to save the resource as a file.
    */
    /*************************************************************************/
    void Save() const noexcept(false);

    /*************************************************************************/
    /*!
      \brief
        Gets the file path for this resource.
      \returns
        The string for the path this resource is in.
    */
    /*************************************************************************/
    const std::string& GetPath() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the file name for this resource.
      \returns
        The string for the resource's file name.
    */
    /*************************************************************************/
    const std::string& GetFileName() const;

  protected:

    /*************************************************************************/
    /*!
      \brief
        Saves the file to the specified file path. The file path
        is the concatenation of the filename and path variables
        found in the resource class.
      \param filepath
        The concatenation of the path and filename in the order
        of "path_/filename_".
      \throws Barrage::RuntimeError
        If this failed to save the resource.
    */
    /*************************************************************************/
    virtual void Save(const std::string& filepath) const noexcept(false) = 0;
    /*************************************************************************/
    /*!
      \brief
        Loads a resource using a concatanted file path.
        The file path is created using the path and filename variables
        stored in the resource.
      \param filepath
        The concatenation of the path and filename in the order
        of "path_/filename_".
      \throws Barrage::RuntimeError
        If we failed to load the resource at the given file name and path.
    */
    /*************************************************************************/
    virtual void Load(const std::string& filepath) noexcept(false) = 0;
    /*************************************************************************/
    /*!
      \brief
        Checks whether the filename has a filename extension.
      \returns
        - True if the filename has a filename extension, false otherwise.
    */
    /*************************************************************************/
    bool HasFilenameExtension() const;

  private:
    //! The path in disk to find the file.
    std::string path_;
    //! The name of the file.
    std::string filename_;

  };
  //! The file manager which provides utility for saving and loading files
  //! In the appropriate places.
  class FileManager
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Initializes the file manager paths using the given operating system.
      \param userPathAppend
        The file path appended by the regular user directory specified
        by the operating systemm.
    */
    /*************************************************************************/
    void Initialize(const std::string& userPathAppend = "Barrage/");
    /*************************************************************************/
    /*!
      \brief
        Releases all cached resources.
    */
    /*************************************************************************/
    void Shutdown();
    /*************************************************************************/
    /*!
      \brief
        Saves a particular resource through this manager.
      \remark
        For the meantime, this is equivalent to calling "Save" on the actual
        resource but that may change in the future.
    */
    /*************************************************************************/
    void Save(const FileResource& file) const;
    /*************************************************************************/
    /*!
      \brief
        Looks for a resource stored in this file manager. If a resource
        with an identical path and filename is found it just returns that.
        Otherwise, this creates a resource of a given type and loads it 
        using the file path and name.
      \param path
        The path in disk to load the resource.
      \param name
        The name of the resource being loaded, excluding the file type.
      \tparam T
        The type of resource being loaded.
      \throws Barrage::RuntimeError
        If we failed to load the resource specified, check the exception
        object for an error message.
      \remark
        Using a file extension is allowed to specify a
        more specific resource.
        For example using a "image.png" might give the resource
        a hint to look for that image specifically instead of an "image.jpg".
        Otherwise an "image" might look for either.
        For more details on search paths, check the documentation for
        the resource being loaded.
    **/
    /*************************************************************************/
    template <typename T>
    const T& Load(const std::string_view& path, const std::string_view& filename) noexcept(false);
    /*************************************************************************/
    /*!
      \brief
        Unloads a particular resource from this manager with the given
        path which includes the file name.
      \param filepath
        The file path to the resource to unload.
      \remark
        If the resource is not found, this function does nothing.
    **/
    /*************************************************************************/
    void Unload(const std::string_view& filepath);
    /*************************************************************************/
    /*!
      \brief
        Creates a resource given the path to save it to and it's file
        name.
      \param path
        The path this resource would save to.
      \param filename
        The file name for this resource.
      \returns
        A reference to the resource created.
      \throws Barrage::RuntimeError
        If the user attempted to create a resource with the same
        path and filename as another, existing, resource.
    **/
    /*************************************************************************/
    template <typename T>
    T& Create(const std::string_view& path, const std::string_view& filename) noexcept(false);
    /*************************************************************************/
    /*!
      \brief
        Gets the path to the user directory.
      \returns
        The string holding the user directory.
    */
    /*************************************************************************/
    const std::string& GetUserPath() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the path to the content directory.
      \returns
        The string holding the content directory.
    */
    /*************************************************************************/
    const std::string& GetContentPath() const;

  private:
    //! The path to the user directory.
    std::string userPath_;
    //! The relative path from the executable to the content directory.
    std::string contentPath_;
    //! The resources cached by this system in case things get loaded
    //! repeatedly.
    std::map<std::string, FileResource*> cachedResources_;

    /*************************************************************************/
    /*!
      \brief
        A helper function that queries the user path from the operating
        system.
      \returns
        The user path without any of the appending done by this system.
    */
    /*************************************************************************/
    static std::string QueryUserPath();
    /*************************************************************************/
    /*!
      \brief
        A helper function that queries the content path.
      \returns
        The content path to any assets that are loaded with the engine.
    */
    /*************************************************************************/
    static std::string QueryContentPath();
  };
}

#include "FileManager.tpp"
#endif // FileManager_MODULE_H
