
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

#include "dynamic_static/system/opengl/buffer.hpp"

namespace dst {
namespace sys {
namespace gl {

/**
Provides high level control over an OpenGL index buffer
*/
class IndexBuffer final
    : public Buffer
{
public:
    /**
    Constructs an instance of IndexBuffer
    */
    IndexBuffer();

    /**
    Moves an instance of IndexBuffer
    @param [in] other The IndexBuffer to move from
    */
    IndexBuffer(IndexBuffer&& other) noexcept;

    /**
    Moves an instance of IndexBuffer
    @param [in] other The IndexBuffer to move from
    @return A reference to this IndexBuffer
    */
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    /**
    TODO : Documentation
    */
    GLenum element_type() const;
};

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
