
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/graphics/opengl/buffer.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include <utility>

namespace dst {
namespace gfx {
namespace gl {

Buffer::Buffer()
{
    set_name("GlBuffer");
}

Buffer::Buffer(GLenum target)
    : mTarget { target }
{
    set_name("GlBuffer");
    dst_gl(glGenBuffers(1, &mHandle));
}

Buffer::Buffer(Buffer&& other) noexcept
{
    *this = std::move(other);
}

Buffer::~Buffer()
{
    dst_gl(glDeleteBuffers(1, &mHandle));
}

Buffer& Buffer::operator=(Buffer&& other) noexcept
{
    assert(this != &other);
    Object::operator=(std::move(other));
    mTarget = std::move(other.mTarget);
    mElementSize = std::move(other.mElementSize);
    mElementCount = std::move(other.mElementCount);
    mMappedPtr = std::move(other.mMappedPtr);
    other.mTarget = 0;
    other.mElementSize = 0;
    other.mElementCount = 0;
    other.mMappedPtr = nullptr;
    return *this;
}

GLsizei Buffer::size() const
{
    return mElementSize * mElementCount;
}

bool Buffer::empty() const
{
    return mElementCount == 0;
}

GLsizei Buffer::element_size() const
{
    return mElementSize;
}

GLsizei Buffer::element_count() const
{
    return mElementCount;
}

const void* Buffer::mapped_ptr() const
{
    return mMappedPtr;
}

void* Buffer::mapped_ptr()
{
    return mMappedPtr;
}

void Buffer::bind() const
{
    assert(mHandle);
    dst_gl(glBindBuffer(mTarget, mHandle));
}

void Buffer::unbind() const
{
    assert(mHandle);
    dst_gl(glBindBuffer(mTarget, 0));
}

void* Buffer::map(GLenum access, GLenum usage)
{
    assert(mHandle);
    if (!mMappedPtr) {
        bind();
        if (usage == GL_STREAM_DRAW) {
            dst_gl(glBufferData(mTarget, size(), nullptr, usage));
        }
        dst_gl(mMappedPtr = glMapBuffer(mTarget, access));
    }
    return mMappedPtr;
}

void Buffer::unmap()
{
    assert(mHandle);
    if (mMappedPtr) {
        bind();
        dst_gl(glUnmapBuffer(mTarget));
        mMappedPtr = nullptr;
        unbind();
    }
}

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
