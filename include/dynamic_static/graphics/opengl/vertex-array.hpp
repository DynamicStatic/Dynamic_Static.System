
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

#include "dynamic_static/graphics/opengl/object.hpp"

namespace dst {
namespace gfx {
namespace gl {

/**
Provides high level control over an OpenGL vertex array
*/
class VertexArray final
    : public Object
{
public:
    /**
    Constructs an instance of VertexArray
    */
    VertexArray();

    /**
    Moves an instance of VertexArray
    @param [in] other The VertexArray to move from
    */
    VertexArray(VertexArray&& other) noexcept;

    /**
    Destroys this instance of VertexArray
    */
    ~VertexArray() override final;

    /**
    Moves an instance of VertexArray
    @param [in] other The VertexArray to move from
    @return A reference to this VertexArray
    */
    VertexArray& operator=(VertexArray&& other) noexcept;

    /**
    TODO : Documentation
    */
    void bind() const;

    /**
    TODO : Documentation
    */
    void unbind() const;
};

} // namespace gl
} // namespace gfx
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
