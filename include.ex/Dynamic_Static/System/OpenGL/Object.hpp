
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
#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)

#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/StringUtilities.hpp"
#include "Dynamic_Static/System/OpenGL/Defines.hpp"

#include <string>
#include <utility>

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*
    * Common base for OpenGL Objects.
    */
    class Object
        : NonCopyable
    {
    protected:
        GLuint mHandle { 0 };

    private:
        std::string mName { "GLObject(0)" };

    public:
        /*
        * Constructs an instance of Object.
        */
        Object() = default;

        /*
        * Moves an instance of Object.
        * @param [in] other The Object to move from
        */
        Object(Object&& other)
        {
            *this = std::move(other);
        }

        /*
        * Moves an instance of Object.
        * @param [in] other The Object to move from
        * @return This Object
        */
        Object& operator=(Object&& other)
        {
            if (this != &other) {
                mHandle = std::move(other.mHandle);
                mName = std::move(other.mName);
                other.mHandle = 0;
            }
            return *this;
        }

        /*
        * Converts this Object to its handle
        * @return This Object's handle
        */
        operator GLuint() const
        {
            return mHandle;
        }

        /*
        * Converts this Object to a value indicating whether or not its valid.
        * @return Whether or not this Object is valid
        */
        operator bool() const
        {
            return mHandle != 0;
        }

    public:
        /*
        * Gets this Object's name.
        * @return This Object's name
        */
        inline const std::string& get_name() const
        {
            return mName;
        }

        /*
        * Sets this Object's name.
        * @param [in] name This Object's name
        */
        inline void set_name(dst::string_view name)
        {
            mName = name;
            mName += "(" + std::to_string(mHandle) + ")";
        }

        /*
        * Gets this Object's handle.
        * @return This Object's handle
        */
        GLuint get_handle() const
        {
            return mHandle;
        }
    };

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
