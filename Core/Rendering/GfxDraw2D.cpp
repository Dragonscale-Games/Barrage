﻿/* ========================================================================= */
/*!
 *
 * \file            GfxDraw2D.hpp
 * \author          David Wong Cascante
 * \par             david.wongcascante\@digipen.edu

 * \brief
 * Defines a simplified interface that manages the renderer.
 * The interface becomes nicer and whatnot.
 */
 /* ========================================================================= */

//  ===========================================================================
// INCLUDES
//  ===========================================================================
#include "GfxDraw2D.hpp"
#include <cassert>

#include "GfxPrimitives.hpp"

namespace Barrage
{
  GfxDraw2D::GfxDraw2D() : manager_(nullptr), renderer_(nullptr)
  {
  }

  void GfxDraw2D::Initialize(GfxManager2D& manager, GfxRenderer2D& renderer)
  {
    // Get the pointer to the renderer.
    renderer_ = &renderer;
    manager_ = &manager;
    // Create the vertex information for the quad mesh.
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    GenQuadInfo(vertices, faces);
    // Create the mesh using the vertex information.
    GfxManager2D::MeshSpecs specs = {};
    specs.buffer_ = vertices.data();
    specs.indices_ = faces.data();
    specs.bufferLength_ = vertices.size();
    specs.indicesLength_ = faces.size();
    specs.bufferElementSize_ = sizeof(vertices.front());
    specs.indicesElementSize_ = sizeof(faces.front());
    quad_ = manager_->CreateMesh(specs);
  }

  void GfxDraw2D::DrawQuad(
    const glm::vec2& position, const glm::vec2& scale, const RADIAN& rotation,
    const GfxManager2D::TextureID& textureID)
  {
    assert(renderer_);
  }

  void GfxDraw2D::DrawInstancedQuad(
    bool instanced, int count,
    const glm::vec2* positions, const glm::vec2* scales,
    const RADIAN* rotations, const GfxManager2D::TextureID& texture)
  {
    assert(renderer_);
    // Fill out a render request form.
    GfxRenderer2D::InstancedRequest request = {};
    // Set the resources for the request.
    request.resources_.framebuffer_ = boundFrame_;
    request.resources_.shader_ = boundShader_;
    request.resources_.mesh_ = quad_;
    request.resources_.texture_ = texture;
    // Set the transform data for the request.
    request.transform_.count_ = count;
    request.transform_.positions_ = positions;
    request.transform_.scales_ = scales;
    request.transform_.rotations_ = rotations;
    // And send the request to the renderer.
    renderer_->AddRequest(request);
  }

  void GfxDraw2D::ApplyShader(const GfxManager2D::ShaderID& shader)
  {
    boundShader_ = shader;
  }

}
