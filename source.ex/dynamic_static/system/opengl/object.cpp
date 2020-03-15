
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/opengl/object.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include <utility>

namespace dst {
namespace sys {
namespace gl {

Object::~Object()
{
}

Object::operator GLuint() const
{
    return mHandle;
}

Object::operator bool() const
{
    return mHandle != 0;
}

GLuint Object::get_handle() const
{
    return mHandle;
}

const std::string& Object::get_name() const
{
    return mName;
}

void Object::set_name(const std::string& name)
{
    mName = name;
}

Object::Object(Object&& other) noexcept
{
    *this = std::move(other);
}

Object& Object::operator=(Object&& other) noexcept
{
    assert(this != &other);
    mHandle = std::move(other.mHandle);
    mName = std::move(other.mName);
    other.mHandle = 0;
    return *this;
}

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
