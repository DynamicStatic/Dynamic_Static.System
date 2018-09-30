
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

#include "Dynamic_Static/System/OpenGL/Defines.hpp"
#include "Dynamic_Static/System/OpenGL/Object.hpp"

#include <string>
#include <utility>

namespace dst {
namespace sys {
namespace gl {

    /*!
    Provides high level control over an OpenGL buffer.
    */
    class Buffer
        : public Object
    {
    private:
        GLenum mTarget { 0 };
        GLsizei mElementSize { 0 };
        GLsizei mElementCount { 0 };
        void* mMappedPtr { nullptr };

    public:
        /*!
        Constructs an instance of Buffer.
        */
        inline Buffer()
        {
            set_name("Buffer");
        }

        /*!
        Constructs an instance of Buffer.
        @param [in] type This Buffer's type
        */
        inline Buffer(GLenum type)
            : mTarget { type }
        {
            set_name("Buffer");
            dst_gl(glGenBuffers(1, &mHandle));
        }

        /*!
        Destroys this instance of Buffer.
        */
        inline ~Buffer()
        {
            if (mHandle) {
                dst_gl(glDeleteBuffers(1, &mHandle));
            }
        }

        /*!
        Moves an instance of Buffer.
        @param [in] other The Buffer to move from
        */
        inline Buffer(Buffer&& other)
        {
            *this = std::move(other);
        }

        /*!
        Moves an instance of Buffer.
        @param [in] other The Buffer to move from
        @return This Buffer
        */
        inline Buffer& operator=(Buffer&& other)
        {
            if (this != &other) {
                Object::operator=(std::move(other));
                mTarget = std::move(other.mTarget);
                mElementSize = std::move(other.mElementSize);
                mElementCount = std::move(other.mElementCount);
                mMappedPtr = std::move(other.mMappedPtr);
                other.mMappedPtr = nullptr;
            }
            return *this;
        }

    public:
        /*!
        Gets a value indicating whether or not this Buffer is empty.
        @return Whether or not this Buffer is empty
        */
        inline bool empty() const
        {
            return mElementCount == 0;
        }

        /*!
        Gets the size in bytes of a single element in this Buffer.
        @return The size in bytes of a single element in this Buffer
        */
        inline GLsizei get_element_size() const
        {
            return mElementSize;
        }

        /*!
        Gets the number of elements in this Buffer.
        @return The number of elements in this Buffer
        */
        inline GLsizei get_element_count() const
        {
            return mElementCount;
        }

        /*!
        Gets this Buffer's size in bytes.
        @return This Buffer's size in bytes
        */
        inline GLsizei get_size() const
        {
            return mElementSize * mElementCount;
        }

        /*!
        Gets this Buffer's mapped ptr.
        @return This Buffer's mapped ptr or nullptr if this Buffer isn't mapped
        */
        inline void* get_mapped_ptr()
        {
            return mMappedPtr;
        }

        /*!
        Gets this Buffer's mapped ptr.
        @return This Buffer's mapped ptr or nullptr if this Buffer isn't mapped
        */
        inline const void* get_mapped_ptr() const
        {
            return mMappedPtr;
        }

        /*!
        Binds this Buffer using its OpenGL target.
        */
        inline void bind() const
        {
            dst_gl(glBindBuffer(mTarget, mHandle));
        }

        /*!
        Unbinds the Buffer at this Buffer's OpenGL target.
        */
        inline void unbind() const
        {
            dst_gl(glBindBuffer(mTarget, 0));
        }

        /*!
        Maps this Buffer.
        @param [in] access This Buffer's access policy given as GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE (optional = GL_WRITE_ONLY)
        @param [in] usage This Buffer's usage pattern given as GL_ STREAM/STATIC/DYNAMIC_ DRAW/READ/COPY (optional = GL_STREAM_DRAW)
        */
        inline void* map(
            GLenum access = GL_WRITE_ONLY,
            GLenum usage = GL_STREAM_DRAW
        )
        {
            if (!mMappedPtr) {
                bind();
                if (usage == GL_STREAM_DRAW) {
                    dst_gl(glBufferData(mTarget, get_size(), nullptr, usage));
                }
                dst_gl(mMappedPtr = glMapBuffer(mTarget, access));
                unbind();
            }
            return mMappedPtr;
        }

        /*!
        Unmaps this Buffer.
        */
        inline void unmap()
        {
            if (mMappedPtr) {
                bind();
                dst_gl(glUnmapBuffer(mTarget));
                mMappedPtr = nullptr;
                unbind();
            }
        }

        /*!
        Writes data to this Buffer.
        @param <T> The type of data to write to this Buffer
        @param [in] data The data to write to this Buffer
        @param [in](optional = GL_STATIC_DRAW) usage This Buffer's usage pattern given as GL_ STREAM/STATIC/DYNAMIC_ DRAW/READ/COPY
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
            dst_gl(glBufferData(mTarget, get_size(), data.data(), usage));
            unbind();
        }
    };

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
