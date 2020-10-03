
/*
==========================================
    Copyright 2017-2019 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/graphics/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/graphics/opengl/buffer.hpp"

namespace dst {
namespace gfx {
namespace gl {

/**
Provides high level control over an OpenGL vertex buffer
*/
class VertexBuffer final
    : public Buffer
{
public:
    /**
    Constructs an instance of VertexBuffer
    */
    VertexBuffer();

    /**
    Moves an instance of VertexBuffer
    @param [in] other The VertexBuffer to move from
    */
    VertexBuffer(VertexBuffer&& other) noexcept;

    /**
    Moves an instance of VertexBuffer
    @param [in] other The VertexBuffer to move from
    @return A reference to this VertexBuffer
    */
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;
};

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
