
/*
==========================================
    Copyright 2017-2019 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/opengl/vertex-buffer.hpp"

#ifdef DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED

#include <utility>

namespace dst {
namespace sys {
namespace gl {

VertexBuffer::VertexBuffer()
    : Buffer(GL_ARRAY_BUFFER)
{
    set_name("GlVertexBuffer");
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
{
    *this = std::move(other);
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    assert(this != &other);
    Buffer::operator=(std::move(other));
    return *this;
}

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
