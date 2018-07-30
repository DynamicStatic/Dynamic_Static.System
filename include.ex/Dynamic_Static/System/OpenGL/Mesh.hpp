
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
#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)

#include "Dynamic_Static/Core/StringUtilities.hpp"
#include "Dynamic_Static/System/OpenGL/Defines.hpp"
#include "Dynamic_Static/System/OpenGL/IndexBuffer.hpp"
#include "Dynamic_Static/System/OpenGL/Vertex.hpp"
#include "Dynamic_Static/System/OpenGL/VertexArray.hpp"
#include "Dynamic_Static/System/OpenGL/VertexBuffer.hpp"

#include "gsl/span"

#include <string>

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*
    * Provides high level control over an OpenGL mesh.
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
        /*
        * Writes vertex and index data to this Mesh.
        * @param <VertexType> The type of vertex data to write to this Mesh
        * @param <IndexType> The type of index data to write to this Mesh
        * @param [in] vertices The vertex data to write to this Mesh
        * \n NOTE : VertexType must have dstgl::enable_vertex_attributes<> specialized
        * @param [in] indices The index data to write to this Mesh
        * @param [in](optional = GL_STATIC_DRAW) usage This Mesh's usage pattern given as GL_ STREAM/STATIC/DYNAMIC_ DRAW/READ/COPY
        */
        template <
            typename VertexType,
            typename IndexType
        >
        inline void write(
            gsl::span<VertexType> vertices,
            gsl::span<IndexType> indices,
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

        /*
        * Draws this Mesh.
        */
        inline void draw() const
        {
            vertexArray.bind();
            dst_gl(glFrontFace(windingMode));
            dst_gl(glPolygonMode(GL_FRONT_AND_BACK, fillMode));
            dst_gl(glDrawElements(prmitiveType, indexBuffer.get_element_count(), indexBuffer.get_element_type(), nullptr));
            vertexArray.unbind();
        }
    };

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
