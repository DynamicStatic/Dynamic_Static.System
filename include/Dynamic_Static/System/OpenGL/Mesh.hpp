
/*
==========================================
    Copyright 2017-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED

#include "Dynamic_Static/System/OpenGL/Defines.hpp"
#include "Dynamic_Static/System/OpenGL/IndexBuffer.hpp"
#include "Dynamic_Static/System/OpenGL/Vertex.hpp"
#include "Dynamic_Static/System/OpenGL/VertexArray.hpp"
#include "Dynamic_Static/System/OpenGL/VertexBuffer.hpp"

#include <string>

namespace dst {
namespace sys {
namespace gl {

    /*!
    Provides high level control over an OpenGL mesh.
    */
    class Mesh final
    {
    public:
        std::string name { "Mesh" };          /*!< This Mesh's name */
        VertexBuffer vertexBuffer;            /*!< This Mesh's VertexBuffer */
        IndexBuffer indexBuffer;              /*!< This Mesh's IndexBuffer */
        VertexArray vertexArray;              /*!< This Mesh's VertexArray */
        GLenum windingMode { GL_CW };         /*!< This Mesh's winding mode */
        GLenum fillMode { GL_FILL };          /*!< This Mesh's fill mode */
        GLenum prmitiveType { GL_TRIANGLES }; /*!< This Mesh's primitive type */

    public:
        /*!
        Writes vertex and index data to this Mesh.
        @param <VertexType> The type of vertex data to write to this Mesh
        @param <IndexType> The type of index data to write to this Mesh
        @param [in] vertices The vertex data to write to this Mesh
        \n NOTE : VertexType must have dstgl::enable_vertex_attributes<> specialized
        @param [in] indices The index data to write to this Mesh
        @param [in](optional = GL_STATIC_DRAW) usage This Mesh's usage pattern given as GL_ STREAM/STATIC/DYNAMIC_ DRAW/READ/COPY
        */
        template <
            typename VertexType,
            typename IndexType
        >
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
            dstgl::enable_vertex_attributes<VertexType>();
            vertexArray.unbind();
        }

        /*!
        Draws this Mesh.
        */
        inline void draw_indexed() const
        {
            draw_indexed(indexBuffer.get_element_count(), nullptr);
        }

        /*!
        Draws this Mesh.
        @param [in] count The number of vertices to draw
        @param [in] indices A pointer into this Mesh's IndexBuffer to start drawing from
        \n NOTE : This pointer treats the start of this Mesh's IndexBuffer storage as address 0
        */
        inline void draw_indexed(
            GLsizei count,
            const void* indices
        ) const
        {
            vertexArray.bind();
            dst_gl(glFrontFace(windingMode));
            dst_gl(glPolygonMode(GL_FRONT_AND_BACK, fillMode));
            dst_gl(glDrawElements(prmitiveType, count, indexBuffer.get_element_type(), indices));
            vertexArray.unbind();
        }
    };

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
