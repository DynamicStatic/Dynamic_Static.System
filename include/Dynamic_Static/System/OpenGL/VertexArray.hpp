
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
#include "Dynamic_Static/System/OpenGL/Object.hpp"

#include <utility>

namespace dst {
namespace sys {
namespace gl {

    /*!
    Provides high level control over an OpenGL vertex array
    */
    class VertexArray final
        : public Object
    {
    public:
        /*!
        Constructs an instance of VertexArray
        */
        inline VertexArray()
        {
            set_name("VertexArray");
            dst_gl(glGenVertexArrays(1, &mHandle));
        }

        /*!
        Moves an instance of VertexArray
        @param [in] other The VertexArray to move from
        */
        inline VertexArray(VertexArray&& other)
        {
            *this = std::move(other);
        }

        /*!
        Destroys this instance of VertexArray
        */
        inline ~VertexArray()
        {
            if (mHandle) {
                dst_gl(glDeleteVertexArrays(1, &mHandle));
            }
        }

        /*!
        Moves an instance of VertexArray
        @param [in] other The VertexArray to move from
        @return This VertexArray
        */
        inline VertexArray& operator=(VertexArray&& other)
        {
            if (this != &other) {
                Object::operator=(std::move(other));
            }
            return *this;
        }

    public:
        /*!
        Binds this VertexArray
        */
        inline void bind() const
        {
            dst_gl(glBindVertexArray(mHandle));
        }

        /*!
        Unbinds the current VertexArray
        */
        inline void unbind() const
        {
            dst_gl(glBindVertexArray(0));
        }
    };

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
