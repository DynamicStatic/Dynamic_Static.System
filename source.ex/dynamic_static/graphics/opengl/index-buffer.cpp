
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/graphics/opengl/index-buffer.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include <utility>

namespace dst {
namespace gfx {
namespace gl {

IndexBuffer::IndexBuffer()
    : Buffer(GL_ELEMENT_ARRAY_BUFFER)
{
    set_name("GlIndexBuffer");
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
{
    *this = std::move(other);
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    assert(this != &other);
    Buffer::operator=(std::move(other));
    return *this;
}

GLenum IndexBuffer::element_type() const
{
    switch (element_size()) {
    case sizeof(uint8_t): return GL_UNSIGNED_BYTE;
    case sizeof(uint16_t): return GL_UNSIGNED_SHORT;
    case sizeof(uint32_t): return GL_UNSIGNED_INT;
    default: {
        assert(false);
        return 0;
    }
    }
}

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
