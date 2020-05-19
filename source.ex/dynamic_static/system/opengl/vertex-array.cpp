
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/opengl/vertex-array.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include <cassert>
#include <utility>

namespace dst {
namespace sys {
namespace gl {

VertexArray::VertexArray()
{
    set_name("GlVertexArray");
    dst_gl(glGenVertexArrays(1, &mHandle));
}

VertexArray::VertexArray(VertexArray&& other) noexcept
{
    *this = std::move(other);
}

VertexArray::~VertexArray()
{
    dst_gl(glDeleteVertexArrays(1, &mHandle));
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    assert(this != &other);
    Object::operator=(std::move(other));
    return *this;
}

void VertexArray::bind() const
{
    dst_gl(glBindVertexArray(mHandle));
}

void VertexArray::unbind() const
{
    dst_gl(glBindVertexArray(0));
}

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
