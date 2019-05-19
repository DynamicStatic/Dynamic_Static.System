
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

#include "Dynamic_Static/System/OpenGL/Defines.hpp"

#include <string>
#include <utility>

namespace dst {
namespace sys {
namespace gl {

    /*!
    Common base for OpenGL Objects
    */
    class Object
        : NonCopyable
    {
    protected:
        GLuint mHandle { 0 };

    private:
        std::string mName { "GLObject" };

    public:
        /*!
        Constructs an instance of Object
        */
        inline Object() = default;

        /*!
        Moves an instance of Object
        @param [in] other The Object to move from
        */
        inline Object(Object&& other)
        {
            *this = std::move(other);
        }

        /*!
        Moves an instance of Object
        @param [in] other The Object to move from
        @return This Object
        */
        inline Object& operator=(Object&& other)
        {
            if (this != &other) {
                mHandle = std::move(other.mHandle);
                mName = std::move(other.mName);
                other.mHandle = 0;
            }
            return *this;
        }

        /*!
        Converts this Object to its OpenGL handle
        @return This Object's OpenGL handle
        */
        inline operator GLuint() const
        {
            return mHandle;
        }

        /*!
        Converts this Object to a value indicating whether or not its valid
        @return Whether or not this Object is valid
        */
        inline operator bool() const
        {
            return mHandle != 0;
        }

    public:
        /*!
        Gets this Object's name
        @return This Object's name
        */
        inline const std::string& get_name() const
        {
            return mName;
        }

        /*!
        Sets this Object's name
        @param [in] name This Object's name
        */
        inline void set_name(dst::StringView name)
        {
            mName = name;
        }

        /*!
        Gets this Object's OpenGL handle
        @return This Object's OpenGL handle
        */
        inline GLuint get_handle() const
        {
            return mHandle;
        }
    };

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
