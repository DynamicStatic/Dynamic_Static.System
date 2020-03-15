
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/opengl/defines.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include <string>

namespace dst {
namespace sys {
namespace gl {

/**
TODO : Documentation
*/
class Object
{
public:
    /**
    Contructs an instance of Object
    */
    Object() = default;

    /**
    Destroys this instance of Object
    */
    virtual ~Object() = 0;

    /**
    TODO : Documentation
    */
    operator GLuint() const;

    /**
    TODO : Documentation
    */
    operator bool() const;

    /**
    TODO : Documentation
    */
    GLuint get_handle() const;

    /**
    TODO : Documentation
    */
    const std::string& get_name() const;

    /**
    TODO : Documentation
    */
    void set_name(const std::string& name);

protected:
    /**
    TODO  : Documentation
    */
    Object(Object&& other) noexcept;

    /**
    TODO : Documentation
    */
    Object& operator=(Object&& other) noexcept;

    GLuint mHandle { 0 }; //!< TODO : Documentation

private:
    std::string mName { "GlObject" };
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
};

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
