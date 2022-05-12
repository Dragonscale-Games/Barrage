/* ========================================================================= */
/*!
 *
 * \file            GfxTypes.hpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Encompasses utility functions for graphics programs.
 */
 /* ========================================================================= */

////////////////////////////////////////////////////////////////////////////////
#ifndef GfxUtil_MODULE_H
#define GfxUtil_MODULE_H
////////////////////////////////////////////////////////////////////////////////

//  ===========================================================================
// Includes
//  ===========================================================================
#include <glm/vec2.hpp>

namespace Barrage
{
 struct Vertex //! Represents a single vertex inside a mesh.
  {
    /*************************************************************************/
    /*!
      \brief
        Creates a vertex that has a position at the origin
        and the uv coordinates on the bottom left corner of the image.
    */
    /*************************************************************************/
    Vertex();
    /*************************************************************************/
    /*!
      \brief
        Constructs a vertex given it's position in 2D space
        and the UV texture coordinate it corresponds to.
      \param position
        The position of the vertex in 2D space.
      \param uvCoordinate
        The point in the texture that part the mesh gets mapped to.
    */
    /*************************************************************************/
    Vertex(const glm::vec2& position, const glm::vec2& uvCoordinate);

    glm::vec2 position_;        //!< The position of the vertex in 2D space.
    glm::vec2 uvCoordinate_;    //!< The texture coordinate in UV coordinates.
  };

  union Face //! Indicates which vertices correspond with which faces.
  {
    /*************************************************************************/
    /*!
      \brief
        Creates a face in which all the indices point to the first
        vertex of the face.
    */
    /*************************************************************************/
    Face();
    /*************************************************************************/
    /*!
      \brief
        Constructs a face given the three indices to the vertices 
        it is made out of.
      \param vertex1
        The first vertex in the face.
      \param vertex2
        The second vertex in the face.
      \param vertex3
        The third vertex in the face.
    */
    /*************************************************************************/
    Face(unsigned vertex1, unsigned vertex2, unsigned vertex3);

    struct
    {
      unsigned vertex1_;    //!< The first vertex of the face.
      unsigned vertex2_;    //!< The second vertex of the face.
      unsigned vertex3_;    //!< The third vertex of the face.
    };

    unsigned vertices_[3];  //!< The three vertices that make up a face.
  };

  enum TextureFormat //! Enumerates the available formats for the textures.
  {
    R8G8B8A8,
    R8G8B8,
    R8G8,
    R8,
  };

  enum TextureFilter //! Enumerates the available filters for textures.
  {
    FILTER_NONE,
    FILTER_LINEAR,
  };
}

#endif // GfxUtil_MODULE_H
