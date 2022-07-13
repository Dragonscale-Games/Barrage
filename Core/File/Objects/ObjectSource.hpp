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
#ifndef ArchetypeSource_MODULE_H
#define ArchetypeSource_MODULE_H
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
    /*************************************************************************/
    ObjectSource(const std::string& path, const std::string& filepath);
    /*************************************************************************/
    /*************************************************************************/
    ObjectSource(ObjectSource&& other) = default;
    /*************************************************************************/
    /*************************************************************************/
    virtual ~ObjectSource() override = default;

    /*************************************************************************/
    /*************************************************************************/
    const rapidjson::Document& GetDocument() const;
    /*************************************************************************/
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

#endif // ArchetypeSource_MODULE_H
