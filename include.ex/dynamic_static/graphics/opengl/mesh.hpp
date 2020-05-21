
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/graphics/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/core/span.hpp"
#include "dynamic_static/graphics/opengl/index-buffer.hpp"
#include "dynamic_static/graphics/opengl/vertex.hpp"
#include "dynamic_static/graphics/opengl/vertex-array.hpp"
#include "dynamic_static/graphics/opengl/vertex-buffer.hpp"

#include <string>

namespace dst {
namespace gfx {
namespace gl {

/**
Provides high level control over an OpenGL mesh
*/
class Mesh final
{
public:
    /**
    TODO : Documentation
    */
    void draw_indexed() const;

    /**
    TODO : Documentation
    */
    void draw_indexed(GLsizei count, const void* pIndices = nullptr) const;

    /**
    TODO : Documentation
    */
    template <typename VertexType, typename IndexType>
    inline void write(
        dst::Span<VertexType> vertices,
        dst::Span<IndexType> indices,
        GLenum usage = GL_STATIC_DRAW
    )
    {
        vertexBuffer.write(vertices, usage);
        indexBuffer.write(indices, usage);
        vertexArray.bind();
        vertexBuffer.bind();
        indexBuffer.bind();
        enable_vertex_attributes<VertexType>();
        vertexArray.unbind();
    }

    std::string name { "GlMesh" };         //!< TODO : Documentation
    VertexBuffer vertexBuffer;             //!< TODO : Documentation
    IndexBuffer indexBuffer;               //!< TODO : Documentation
    VertexArray vertexArray;               //!< TODO : Documentation
    GLenum windingMode { GL_CW };          //!< TODO : Documentation
    GLenum fillMode { GL_FILL };           //!< TODO : Documentation
    GLenum primitiveType { GL_TRIANGLES }; //!< TODO : Documentation
};

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
