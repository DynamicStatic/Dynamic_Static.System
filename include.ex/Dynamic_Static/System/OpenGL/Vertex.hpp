
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

#include "Dynamic_Static/System/OpenGL/Defines.hpp"

#include <array>

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*
    * Describes vertex attribute for enabling.
    */
    struct VertexAttributeInfo final
    {
        GLenum type { GL_FLOAT };          /*!< The described vertex attribute's type */
        GLint count { 1 };                 /*!< The described vertex attribute's type */
        GLboolean normalized { GL_FALSE }; /*!< Whether or not the described vertex attribute should be normalized */
    };

    /*
    * Enables vertex attributes described by a given std::array<VertexAttributeInfo>.
    * @param <VertexType> The type of vertex to enable attributes for
    * @param <VertexAttributeCount> The number of vertex attriubutes to enable
    * @param [in] vertexAttributeInfos The VertexAttributeInfos describing the vertex attributes to enable
    */
    template <typename VertexType, size_t VertexAttributeCount>
    inline void enable_vertex_attributes(
        const std::array<VertexAttributeInfo, VertexAttributeCount>& vertexAttributeInfos
    )
    {
        GLuint index = 0;
        size_t offset = 0;
        for (const auto& vertexAttributeInfo : vertexAttributeInfos) {
            dst_gl(glEnableVertexAttribArray(index));
            dst_gl(glVertexAttribPointer(
                index,
                vertexAttributeInfo.count,
                vertexAttributeInfo.type,
                vertexAttributeInfo.normalized,
                sizeof(VertexType),
                (GLvoid*)offset
            ));
            size_t elementSize = 0;
            switch (vertexAttributeInfo.type) {
                case GL_BYTE:           elementSize = sizeof(int8_t);   break;
                case GL_UNSIGNED_BYTE:  elementSize = sizeof(uint8_t);  break;
                case GL_SHORT:          elementSize = sizeof(int16_t);  break;
                case GL_UNSIGNED_SHORT: elementSize = sizeof(uint16_t); break;
                case GL_INT:            elementSize = sizeof(int32_t);  break;
                case GL_UNSIGNED_INT:   elementSize = sizeof(uint32_t); break;
                case GL_FLOAT:          elementSize = sizeof(float);    break;
                case GL_DOUBLE:         elementSize = sizeof(double);   break;
            }
            offset += elementSize * vertexAttributeInfo.count;
            ++index;
        }
    }

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

namespace dstgl {

    /*
    * Specializations of this function should call dst::gl::enable_vertex_attributes<> to describe vertex attributes.
    * @param <VertexType> The type of vertex to enable attributes for
    * @example
    *
    *   struct SimpleVertex final
    *   {
    *       glm::vec3 position { };
    *       glm::vec2 texCoord { };
    *   };
    *
    *   namespace dstgl {
    *
    *       template <>
    *       void enable_vertex_attributes<SimpleVertex>()
    *       {
    *           // Our VertexType is SimpleVertex, so we're specializing this
    *           // function and calling enable_vertex_attributes<> with both
    *           // our typename and the number of vertex attributes we're
    *           // enabling...in this case 2 for position and texCoord.
    *           dst::gl::enable_vertex_attributes<SimpleVertex, 2>({{
    *               { GL_FLOAT, 3 }, // position is a vec3, so GL_FLOAT and 3
    *               { GL_FLOAT, 2 }  // texCoord is a vec2, so GL_FLOAT and 2
    *           }});
    *       }
    *
    *   }
    *
    */
    template <typename VertexType>
    inline void enable_vertex_attributes()
    {
    }

} // namespace dstgl

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
