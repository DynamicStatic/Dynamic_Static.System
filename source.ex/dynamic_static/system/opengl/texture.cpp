
/*
==========================================
    Copyright 2017-2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/opengl/texture.hpp"

#ifdef DYNAMIC_STATIC_OPENGL_ENABLED

#include <algorithm>
#include <utility>

namespace dst {
namespace sys {
namespace gl {

Texture::Texture()
{
    set_name("GlTexture");
}

Texture::Texture(
    const Info& info,
    const uint8_t* pData,
    bool generateMipMaps
)
    : mInfo { info }
{
    set_name("GlTexture");
    // TODO : More detailed support for Texture::Info fields
    mInfo.width = std::max(1, mInfo.width);
    mInfo.height = std::max(1, mInfo.height);
    mInfo.depth = std::max(1, mInfo.depth);
    if (mInfo.target == GL_TEXTURE_1D || mInfo.target == GL_TEXTURE_2D) {
        if (mInfo.target == GL_TEXTURE_1D) {
            mInfo.height = 1;
        }
        mInfo.depth = 1;
    }
    create_gl_resources(pData, generateMipMaps);
}

Texture::Texture(Texture&& other) noexcept
{
    *this = std::move(other);
}

Texture::~Texture()
{
    destroy_gl_resources();
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    assert(this != &other);
    Object::operator=(std::move(other));
    mInfo = std::move(other.mInfo);
    other.mInfo = { };
    return *this;
}

const Texture::Info& Texture::info() const
{
    return mInfo;
}

GLsizei Texture::size() const
{
    return
        get_format_bytes_per_pixel(mInfo.format) *
        mInfo.width *
        mInfo.height *
        mInfo.depth;
}

GLint Texture::mip_level_count() const
{
    return 1 + (GLint)(std::floor(std::log2(std::max(mInfo.width, mInfo.height))));
}

void Texture::generate_mip_maps() const
{
    if (mInfo.filter == GL_NEAREST_MIPMAP_NEAREST ||
        mInfo.filter == GL_LINEAR_MIPMAP_NEAREST ||
        mInfo.filter == GL_NEAREST_MIPMAP_LINEAR ||
        mInfo.filter == GL_LINEAR_MIPMAP_LINEAR) {
        bind();
        dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_MAX_LEVEL, mip_level_count()));
        dst_gl(glGenerateMipmap(mInfo.target));
        unbind();
    }
}

void Texture::bind() const
{
    dst_gl(glBindTexture(mInfo.target, mHandle));
}

void Texture::unbind() const
{
    dst_gl(glBindTexture(mInfo.target, 0));
}

void Texture::write(const uint8_t* pData, bool generateMipMaps)
{
    if (pData) {
        bind();
        dst_gl(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
        dst_gl(glTexImage2D(
            mInfo.target,
            0,
            mInfo.internalFormat,
            mInfo.width,
            mInfo.height,
            0,
            mInfo.format,
            mInfo.storageType,
            pData
        ));
        auto magFilter = mInfo.filter == GL_LINEAR_MIPMAP_LINEAR ? GL_LINEAR : mInfo.filter;
        dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_MIN_FILTER, mInfo.filter));
        dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_MAG_FILTER, magFilter));
        dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_WRAP_S, mInfo.wrap));
        dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_WRAP_T, mInfo.wrap));
        if (generateMipMaps) {
            generate_mip_maps();
        }
        unbind();
    }
}

void Texture::create_gl_resources(const uint8_t* pData, bool generateMipMaps)
{
    // TODO : Handle GL_TEXTURE_1D and GL_TEXTURE_3D
    if (!mHandle) {
        dst_gl(glGenTextures(1, &mHandle));
    }
    if (!mInfo.internalFormat) {
        mInfo.internalFormat = mInfo.format;
    }
    write(pData, generateMipMaps);
}

void Texture::destroy_gl_resources()
{
    dst_gl(glDeleteTextures(1, &mHandle));
}

GLsizei get_format_bytes_per_pixel(GLint format)
{
    // TODO : Account for all formats...
    GLsizei bytesPerPixel = 0;
    switch (format) {
    case GL_RED:  return 1;
    case GL_RGB:
    case GL_BGR:  return 3;
    case GL_RGBA:
    case GL_BGRA: return 4;
    default: {
        assert(false);
        return 0;
    }
    }
}

} // namespace gl
} // namespace sys
} // namespace dst

#endif // DYNAMIC_STATIC_OPENGL_ENABLED
