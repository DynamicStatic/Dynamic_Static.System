
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

#include "Dynamic_Static/System/OpenGL/Buffer.hpp"
#include "Dynamic_Static/System/OpenGL/Defines.hpp"

#include <utility>

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*!
    Provides high level control over an OpenGL vertex buffer.
    */
    class VertexBuffer final
        : public Buffer
    {
    public:
        /*!
        Constructs an instance of VertexBuffer.
        */
        inline VertexBuffer()
            : Buffer(GL_ARRAY_BUFFER)
        {
            set_name("VertexBuffer");
        }

        /*!
        Moves an instance of VertexBuffer.
        @param [in] other The VertexBuffer to move from
        */
        inline VertexBuffer(VertexBuffer&& other)
        {
            *this = std::move(other);
        }

        /*!
        Moves an instance of VertexBuffer.
        @param [in] other The VertexBuffer to move from
        @return This VertexBuffer
        */
        inline VertexBuffer& operator=(VertexBuffer&& other)
        {
            if (this != &other) {
                Buffer::operator=(std::move(other));
            }
            return *this;
        }
    };

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
