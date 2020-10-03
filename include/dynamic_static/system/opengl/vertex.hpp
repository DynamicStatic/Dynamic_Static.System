
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED

#include <array>

namespace dst {
namespace sys {
namespace gl {

/**
TODO : Documentation
*/
struct VertexAttribute final
{
    GLenum type { GL_FLOAT };          //!< TODO : Documentation
    GLint count { 1 };                 //!< TODO : Documentation
    GLboolean normalized { GL_FALSE }; //!< TODO : Documentation
};

/**
TODO : Documentation
*/
template <typename VertexType, size_t VertexAttributeCount>
inline void enable_vertex_attributes(const std::array<VertexAttribute, VertexAttributeCount>& vertexAttributes)
{
    GLuint index = 0;
    size_t offset = 0;
    for (const auto& vertexAttribute : vertexAttributes) {
        dst_gl(glEnableVertexAttribArray(index));
        dst_gl(glVertexAttribPointer(
            index,
            vertexAttribute.count,
            vertexAttribute.type,
            vertexAttribute.normalized,
            sizeof(VertexType),
            (GLvoid*)offset
        ));
        size_t elementSize = 0;
        switch (vertexAttribute.type) {
        case GL_BYTE:           elementSize = sizeof(int8_t);   break;
        case GL_UNSIGNED_BYTE:  elementSize = sizeof(uint8_t);  break;
        case GL_SHORT:          elementSize = sizeof(int16_t);  break;
        case GL_UNSIGNED_SHORT: elementSize = sizeof(uint16_t); break;
        case GL_INT:            elementSize = sizeof(int32_t);  break;
        case GL_UNSIGNED_INT:   elementSize = sizeof(uint32_t); break;
        case GL_FLOAT:          elementSize = sizeof(float);    break;
        case GL_DOUBLE:         elementSize = sizeof(double);   break;
        }
        offset += elementSize * vertexAttribute.count;
        ++index;
    }
}

/*!
Specializations of this function must call dst::sys::gl::enable_vertex_attributes<> to describe vertex attributes
@param <VertexType> The type of vertex to enable attributes for
@example

    struct SimpleVertex final
    {
        glm::vec3 position { };
        glm::vec2 texcoord { };
    };

    namespace dst {
    namespace sys {
    namespace gl {

    template <>
    void enable_vertex_attributes<SimpleVertex>()
    {
        // Our VertexType is SimpleVertex, so we're specializing this function and
        //  calling enable_vertex_attributes<>() with both our typename and the number
        //  of VertexAttributes that we're enabling.
        enable_vertex_attributes<SimpleVertex, 2>({{
            { GL_FLOAT, 3 }, // position is a glm::vec3, so GL_FLOAT and 3
            { GL_FLOAT, 2 }, // texcoord is a glm::vec2, so GL_FLOAT and 2
        }});
    }

    } // namespace gl
    } // namespace sys
    } // namespace dst

*/
template <typename VertexType>
inline void enable_vertex_attributes()
{
}

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
