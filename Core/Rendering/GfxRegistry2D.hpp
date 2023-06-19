/* ========================================================================= */
/*!
 *
 * \file            GfxRegistry2D.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * A helper module to register assets given a particular name.
 * Other helper systems use this module to query for assets.
 * 
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef GfxRegistry2D_BARRAGE_H
#define GfxRegistry2D_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

// ============================================================================
// Includes
// ============================================================================
#include <map>
#include <string>
#include "GfxFactory2D.hpp"

namespace Barrage
{
  class GfxRegistry2D
  {
  public:

    //! Define the data structure to hold our resources.
    using ResourceBook = std::map<std::string, GfxManager2D::ResourceID>;
    using PathBook = std::map<std::string, std::string>;

    /*************************************************************************/
    /*!
      \brief
        Sets a registry object in a safe state.
    */
    /*************************************************************************/
    GfxRegistry2D();
    /*************************************************************************/
    /*!
      \brief
        Initializes the registry with the manager and factory used.
      \param factory
        The factory to use for this registry.
    */
    /*************************************************************************/
    void Initialize(GfxFactory2D& factory);
    /*************************************************************************/
    /*!
      \brief
        Shuts down the system by releasing the resources this holds.
    */
    /*************************************************************************/
    void Shutdown();

    /*************************************************************************/
    /*!
      \brief
        Loads a texture with the given path and registers it with the
        same path.
      \param path
        The path to look up and register the texture with.
    */
    /*************************************************************************/
    void RegisterTexture(const char* path, const char* keyname = nullptr);

    /*************************************************************************/
    /*!
      \brief
        Loads a shader with the given path and registers it with the
        same path.
      \param paths
        The paths to look up and register the shader with.
    */
    /*************************************************************************/
    void RegisterShader(
      const char* const paths[ShaderStage::NUM_SHADERS_POSSIBLE], 
      const char* keyname = nullptr
    );

    /*************************************************************************/
    /*!
      \brief
        Gets the texture with the associated keyname.
      \param keyname
        The key of the texture to get.
      \returns
        - A valid texture if an entry with the keyname does exist.
        - An invalid resource if not.
    */
    /*************************************************************************/
    GfxManager2D::ResourceID FindTexture(const char* keyname);
    /*************************************************************************/
    /*!
      \brief
        Gets the shader with the associated keyname.
      \param keyname
        The key of the shader to get.
      \returns
        - A valid shader if an entry with the keyname does exist.
        - An invalid resource if not.
    */
    /*************************************************************************/
    GfxManager2D::ResourceID FindShader(const char* keyname);

    /*************************************************************************/
    /*!
      \brief
        Gets a list of the names of all registered textures.
      \return
        Returns a list of the names of all registered textures.
    */
    /*************************************************************************/
    std::vector<std::string> GetTextureNames();

    /*************************************************************************/
    /*!
      \brief
        Gets the path to a texture.

      \param textureName
        The name of the texture to get the path for.

      \return
        Returns the path of the texture if it exists, otherwise returns an
        empty string.
    */
    /*************************************************************************/
    std::string GetTexturePath(const std::string& textureName);

  private:
    
    //! The pointer to a factory.
    GfxFactory2D* factory_;
    //! The resource book for textures.
    ResourceBook textureBook_;
    //! Holds the paths to the textures
    PathBook texturePaths_;
    //! The resource book for shaders.
    ResourceBook shaderBook_;

    /*************************************************************************/
    /*!
      \brief
        Registers a resource to a particular map.
      \param resource
        The ID to the resource being registered.
      \param keyname
        The key to register the resource with.
      \param resourceBook
        The structure to register the resource.
    */
    /*************************************************************************/
    void Register(
      const GfxManager2D::ResourceID& resource,
      const char* keyname,
      ResourceBook& resourceBook
    );
    /*************************************************************************/
    /*!
      \brief
        Finds a resource from a given particular map.
      \param keyname
        The key to register the resource with.
      \param resourceBook
        The structure to register the resource.
    */
    /*************************************************************************/
    GfxManager2D::ResourceID Find(
      const char* keyname,
      ResourceBook& resourceBook
    );
  };
}

////////////////////////////////////////////////////////////////////////////////
#endif // GfxRegistry2D_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////
