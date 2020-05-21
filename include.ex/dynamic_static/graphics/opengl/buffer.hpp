
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/graphics/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include "dynamic_static/core/span.hpp"
#include "dynamic_static/graphics/opengl/object.hpp"

namespace dst {
namespace gfx {
namespace gl {

/**
TODO : Documentation
*/
class Buffer
    : public Object
{
public:
    /**
    Constructs an instance of Buffer
    */
    Buffer();

    /**
    TODO : Documentation
    */
    Buffer(GLenum target);

    /**
    TODO : Documentation
    */
    Buffer(Buffer&& other) noexcept;

    /**
    Destroys this instance of Buffer
    */
    virtual ~Buffer() override;

    /**
    TODO : Documentation
    */
    Buffer& operator=(Buffer&& other) noexcept;

    /**
    TODO : Documentation
    */
    GLsizei size() const;

    /**
    TODO : Documentation
    */
    bool empty() const;

    /**
    TODO : Documentation
    */
    GLsizei element_size() const;

    /**
    TODO : Documentation
    */
    GLsizei element_count() const;

    /**
    TODO : Documentation
    */
    const void* mapped_ptr() const;

    /**
    TODO : Documentation
    */
    void* mapped_ptr();

    /**
    TODO : Documentation
    */
    void bind() const;

    /**
    TODO : Documentation
    */
    void unbind() const;

    /**
    TODO : Documentation
    */
    void* map(
        GLenum access = GL_WRITE_ONLY,
        GLenum usage = GL_STREAM_DRAW
    );

    /**
    TODO : Documentation
    */
    void unmap();

    /**
    TODO : Documentation
    */
    template <typename T>
    inline void write(
        dst::Span<T> data,
        GLenum usage = GL_STATIC_DRAW
    )
    {
        mElementSize = (GLsizei)sizeof(T);
        mElementCount = (GLsizei)data.size();
        bind();
        dst_gl(glBufferData(mTarget, size(), data.data(), usage));
        unbind();
    }

private:
    GLenum mTarget { 0 };
    GLsizei mElementSize { 0 };
    GLsizei mElementCount { 0 };
    void* mMappedPtr { nullptr };
};

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
