
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/graphics/opengl/mesh.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

namespace dst {
namespace gfx {
namespace gl {

void Mesh::draw(GLint offset, GLsizei count) const
{
    vertexArray.bind();
    offset = std::min(std::max(0, offset), vertexBuffer.element_count());
    count = std::min(count, vertexBuffer.element_count() - offset);
    dst_gl(glDrawArrays(primitiveType, 0, count));
    vertexArray.unbind();
}

void Mesh::draw_indexed() const
{
    draw_indexed(indexBuffer.element_count(), nullptr);
}

void Mesh::draw_indexed(GLsizei count, const void* pIndices) const
{
    vertexArray.bind();
    dst_gl(glFrontFace(windingMode));
    dst_gl(glPolygonMode(GL_FRONT_AND_BACK, fillMode));
    dst_gl(glDrawElements(primitiveType, count, indexBuffer.element_type(), pIndices));
    vertexArray.unbind();
}

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
