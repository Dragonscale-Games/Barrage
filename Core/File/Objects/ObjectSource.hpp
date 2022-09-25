/* ========================================================================= */
/*!
 *
 * \file            ObjectSource.hpp
 * \author          David Wong Cascante
 * \par             dragonscale.games.llc\@gmail.com

 * \brief
 * Defines the interface for loading Barrage objects.
 */
 /* ========================================================================= */

 ////////////////////////////////////////////////////////////////////////////////
#ifndef ObjectSource_MODULE_H
#define ObjectSource_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <File/FileManager.hpp>
#include <rapidjson/document.h>

namespace Barrage
{
  //! Represents a single object as a resource.
  class ObjectSource : public FileResource
  {
  public:
    /*************************************************************************/
    /*!
      \brief
        Creates an object resource given the path to the file and it's name.
      \param path
        The path to load this resource from.
      \param filename
        The name of the file containing the object source.
    */
    /*************************************************************************/
    ObjectSource(const std::string_view& path, const std::string_view& filename) noexcept;
    /*************************************************************************/
    /*!
      \brief
        Moves the contents of one object source to anoter, used
        by the file manager when creating and loading resources.
    */
    /*************************************************************************/
    ObjectSource(ObjectSource&& other) noexcept = default;
    /*************************************************************************/
    /*!
      \brief
        Destroys and release the resources stored in this object.
    */
    /*************************************************************************/
    virtual ~ObjectSource() override = default;

    /*************************************************************************/
    /*!
      \brief
        Gets the internal RapidJson document this object resource
        loaded.
      \returns
        A reference to an read-only version of the document.
    */
    /*************************************************************************/
    const rapidjson::Document& GetDocument() const;
    /*************************************************************************/
    /*!
      \brief
        Gets the internal RapidJson document this object resource
      loaded.
      \returns
        A reference to a mutable version of the document.
    */
    /*************************************************************************/
    rapidjson::Document& GetDocument();

  protected:
    /*************************************************************************/
    /*!
      \brief
        Loads Barrage objects from a JSON file.
      \param filepath
        The file path to load the JSON from.
    */
    /*************************************************************************/
    virtual void Load(const std::string& filepath) noexcept(false) override;
    /*************************************************************************/
    /*!
      \brief
        Saves Barrage objects as a JSON file.
      \param filepath
        The file path to save the JSON to.
    */
    /*************************************************************************/
    virtual void Save(const std::string& filepath) const noexcept(false) override;
  private:
    //! The rapidjson document which represents the file being read/saved.
    rapidjson::Document objectDoc_;
  };
}

#endif // ObjectSource_MODULE_H
