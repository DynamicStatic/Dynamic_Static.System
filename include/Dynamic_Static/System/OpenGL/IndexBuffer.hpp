
/*
==========================================
    Copyright 2017-2019 Dynamic_Static
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

namespace dst {
namespace sys {
namespace gl {

    /*!
    Provides high level control over an OpenGL index buffer
    */
    class IndexBuffer final
        : public Buffer
    {
    public:
        /*!
        Constructs an instance of IndexBuffer
        */
        inline IndexBuffer()
            : Buffer(GL_ELEMENT_ARRAY_BUFFER)
        {
            set_name("IndexBuffer");
        }

        /*!
        Moves an instance of IndexBuffer
        @param [in] other The IndexBuffer to move from
        */
        inline IndexBuffer(IndexBuffer&& other)
        {
            *this = std::move(other);
        }

        /*!
        Moves an instance of IndexBuffer
        @param [in] other The IndexBuffer to move from
        @return This IndexBuffer
        */
        inline IndexBuffer& operator=(IndexBuffer&& other)
        {
            if (this != &other) {
                Buffer::operator=(std::move(other));
            }
            return *this;
        }

    public:
        /*!
        Gets the type of elements in this IndexBuffer
        @return The type of elements in this IndexBuffer
        */
        inline GLenum get_element_type() const
        {
            switch (get_element_size()) {
                case sizeof(uint8_t): return GL_UNSIGNED_BYTE;
                case sizeof(uint16_t): return GL_UNSIGNED_SHORT;
                case sizeof(uint32_t): return GL_UNSIGNED_INT;
                default: return GL_UNSIGNED_INT;
            }
        }
    };

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
