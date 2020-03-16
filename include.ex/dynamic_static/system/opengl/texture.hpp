
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

#include "dynamic_static/core/span.hpp"
#include "dynamic_static/system/opengl/object.hpp"

namespace dst {
namespace sys {
namespace gl {

/**
Provides high level control over an OpenGL texture
*/
class Texture final
    : public Object
{
public:
    /**
    TODO : Documentation
    */
    struct Info final
    {
        GLint target { GL_TEXTURE_2D };         //!< TODO : Documentation
        GLsizei width { 1 };                    //!< TODO : Documentation
        GLsizei height { 1 };                   //!< TODO : Documentation
        GLsizei depth { 1 };                    //!< TODO : Documentation
        GLint format { GL_RGBA };               //!< TODO : Documentation
        GLint internalFormat { 0 };             //!< TODO : Documentation
        GLint storageType { GL_UNSIGNED_BYTE }; //!< TODO : Documentation
        GLint filter { GL_LINEAR };             //!< TODO : Documentation
        GLint wrap { GL_CLAMP_TO_EDGE };        //!< TODO : Documentation
    };

    /**
    Constructs an instance of Texture
    */
    Texture();

    /**
    Constructs an instance of Texture
    TODO : Documentation
    */
    Texture(
        const Info& info,
        const uint8_t* pData = nullptr,
        bool generateMipMaps = false
    );

    /**
    Moves an instance of Texture
    @param [in] other The Texture to move from
    */
    Texture(Texture&& other) noexcept;

    /**
    Destroys this instance of Texture
    */
    ~Texture() override final;

    /**
    Moves an instance of Texture
    @param [in] other The Texture to move from
    @return A reference to this Texture
    */
    Texture& operator=(Texture&& other) noexcept;

    /**
    TODO : Documentation
    */
    const Info& info() const;

    /**
    TODO : Documentation
    */
    GLsizei size() const;

    /**
    TODO : Documentation
    */
    GLint mip_level_count() const;

    /**
    TODO : Documentation
    */
    void generate_mip_maps() const;

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
    void write(const uint8_t* pData, bool generateMipMaps = false);

private:
    void create_gl_resources(const uint8_t* pData, bool generateMipMaps);
    void destroy_gl_resources();
    Info mInfo { };
};

/**
TODO : Documentation
*/
GLsizei get_format_bytes_per_pixel(GLint format);

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
