
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

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*!
    Provides high level control over an OpenGL texture.
    */
    class Texture final
        : public Object
    {
    public:
        /*!
        Configuration parameters for Texture construction.
        */
        struct Info final
        {
            GLint target { GL_TEXTURE_2D };         /*!< The configured Texture's target */
            GLsizei width { 1 };                    /*!< The configured Texture's width */
            GLsizei height { 1 };                   /*!< The configured Texture's height */
            GLsizei depth { 1 };                    /*!< The configured Texture's depth */
            GLint format { GL_RGBA };               /*!< The configured Texture's format */
            GLint internalFormat { 0 };             /*!< The configured Texture's internal format */
            GLint storageType { GL_UNSIGNED_BYTE }; /*!< The configured Texture's storage type */
            GLint filter { GL_LINEAR };             /*!< The configured Texture's filter type */
            GLint wrap { GL_CLAMP_TO_EDGE };        /*!< The configured Textrure's wrap type */
        };

    private:
        Info mInfo { };

    public:
        /*!
        Constructs an instance of Texture.
        */
        inline Texture()
        {
            set_name("Texture");
        }

        /*!
        Constructs an instance of Texture.
        @param [in] info This Texture's Texture::Info
        @param [in] data This Texture's initial data
        */
        inline Texture(
            const Info& info,
            const uint8_t* data
        )
            : mInfo { info }
        {
            set_name("Texture");
            // TODO : More detailed support for every method in here, ie. 1D and 3D textures, mip maps, etc...
            mInfo.width = std::max(1, mInfo.width);
            mInfo.height = std::max(1, mInfo.height);
            mInfo.depth = std::max(1, mInfo.depth);
            if (mInfo.target == GL_TEXTURE_1D || mInfo.target == GL_TEXTURE_2D) {
                if (mInfo.target == GL_TEXTURE_1D) {
                    mInfo.height = 1;
                }
                mInfo.depth = 1;
            }
            create_gl_resources(data);
        }

        /*!
        Moves an instance of Texture.
        @param [in] other The Texture to move from
        */
        inline Texture(Texture&& other)
        {
            *this = std::move(other);
        }

        /*!
        Destroys this instance of Texture.
        */
        inline ~Texture()
        {
            destroy_gl_resources();
        }

        /*!
        Moves an instance of Texture.
        @param [in] other The Texture to move from
        @return This Texture
        */
        inline Texture& operator=(Texture&& other)
        {
            if (this != &other) {
                Object::operator=(std::move(other));
                mInfo = std::move(other.mInfo);
            }
            return *this;
        }

    public:
        /*!
        Gets this Texture's Texture::Info.
        @return This Texture's Texture::Info
        */
        inline const Info& get_info() const
        {
            return mInfo;
        }

        /*!
        Gets this Texture's size in bytes.
        @return This Texture's size in bytes
        */
        inline GLsizei get_size()
        {
            return get_size(mInfo.format, mInfo.width, mInfo.height, mInfo.depth);
        }

        /*!
        Gets this Texture's mip map level count.
        @return This Texture's mip map level count
        */
        inline GLint get_mip_map_level_count() const
        {
            return 1 + (GLint)(std::floor(std::log2(std::max(mInfo.width, mInfo.height))));
        }

        /*!
        Generates mip maps for this Texture.
        */
        inline void generate_mip_maps()
        {
            if (mInfo.filter == GL_NEAREST_MIPMAP_NEAREST ||
                mInfo.filter == GL_LINEAR_MIPMAP_NEAREST ||
                mInfo.filter == GL_NEAREST_MIPMAP_LINEAR ||
                mInfo.filter == GL_LINEAR_MIPMAP_LINEAR) {
                bind();
                dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_MAX_LEVEL, get_mip_map_level_count()));
                dst_gl(glGenerateMipmap(mInfo.target));
                unbind();
            }
        }

        /*!
        Binds this Texture using its OpenGL target.
        */
        inline void bind() const
        {
            dst_gl(glBindTexture(mInfo.target, mHandle));
        }

        /*!
        Unbinds the Texture at this texture's OpenGL target.
        */
        inline void unbind() const
        {
            dst_gl(glBindTexture(mInfo.target, 0));
        }

        /*!
        Gets the Texture size for a given format and dimensions.
        @param [in] format The format to use to calculate size
        @param [in](optional = 1) width The width in pixels to use to calculate size
        @param [in](optional = 1) height The height in pixels to use to calculate size
        @param [in](optional = 1) depth The depth in pixels to use to calculate size
        */
        static inline GLsizei get_size(
            GLint format,
            GLsizei width = 1,
            GLsizei height = 1,
            GLsizei depth = 1
        )
        {
            // TODO : Account for all formats...
            GLsizei bytesPerPixel = 0;
            switch (format) {
                case GL_RED:  bytesPerPixel = 1; break;
                case GL_RGB:
                case GL_BGR:  bytesPerPixel = 3; break;
                case GL_RGBA:
                case GL_BGRA: bytesPerPixel = 4; break;
                default: break;
            }
            return
                bytesPerPixel *
                std::max(1, width) *
                std::max(1, height) *
                std::max(1, depth);
        }

    private:
        inline void create_gl_resources(const uint8_t* data)
        {
            if (!mHandle) {
                dst_gl(glGenTextures(1, &mHandle));
            }
            if (!mInfo.internalFormat) {
                mInfo.internalFormat = mInfo.format;
            }
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
                data
            ));
            auto magFilter = mInfo.filter == GL_LINEAR_MIPMAP_LINEAR ? GL_LINEAR : mInfo.filter;
            dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_MIN_FILTER, mInfo.filter));
            dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_MAG_FILTER, magFilter));
            dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_WRAP_S, mInfo.wrap));
            dst_gl(glTexParameteri(mInfo.target, GL_TEXTURE_WRAP_T, mInfo.wrap));
            generate_mip_maps();
            unbind();
        }

        inline void destroy_gl_resources()
        {
            if (mHandle) {
                dst_gl(glDeleteTextures(1, &mHandle));
            }
        }
    };

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED
