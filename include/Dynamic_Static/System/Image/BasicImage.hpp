
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Format.hpp"

#include <algorithm>

namespace dst {
namespace sys {

    /*!
    Provides high level control over image data
    */
    class BasicImage
    {
    public:
        /*!
        Provides configuration parameters for an Image
        */
        struct Info
        {
            Format format { Format::Unknown }; //!< The Image's Format
            int width { 0 };                   //!< The Image's width
            int height { 0 };                  //!< The Image's height
        };

    public:
        /*!
        Destroys this instance of Image
        */
        virtual ~BasicImage() = 0
        {
        }

    public:
        /*!
        Gets this Image's Image::Info
        @return This Image's Image::Info
        */
        inline const Info& get_info() const
        {
            return mInfo;
        }

        /*!
        Gets this Image's pixel data
        @param <PixelType = uint8_t> The type to interpret this Image's pixel data as
        @return This Image's pixel data
        */
        template <typename PixelType = uint8_t>
        inline Span<const PixelType> get_pixels() const
        {
            return { data(), size_bytes() / sizeof(PixelType) };
        }

        /*!
        Gets this Image's pixel at the given uv coordinate
        \n NOTE : Uv coordinate (0, 0) returns the pixel at the top left corner of this Image
        @param <PixelType = uint8_t> The type to interpret this Image's pixel data as
        @param [in] uv The uv coordinate of the pixel to get
        */
        template <typename PixelType = uint8_t>
        inline const PixelType& get_pixel(glm::ivec2 uv) const
        {
            uv.x = std::clamp(uv.x, 0, mInfo.width - 1);
            uv.y = std::clamp(uv.y, 0, mInfo.height - 1);
            return get_pixels<const PixelType>()[uv.y * mInfo.width + uv.x];
        }

        /*!
        Gets this Image's size in bytes
        @return This Image's size in bytes
        */
        inline size_t size_bytes() const
        {
            return size_bytes(mInfo);
        }

        /*!
        Clears this Image
        */
        virtual void clear() = 0
        {
            mInfo = { };
        }

        /*!
        Gets the size in bytes required for a given Image::Info
        @param [in] info The Image::Info to get the required size in bytes for
        @return This Image's size in bytes
        */
        static size_t size_bytes(const Info& info)
        {
            auto bpp = get_format_bytes_per_pixel(info.format);
            return info.width * info.height * bpp;
        }

    private:
        virtual const uint8_t* data() const = 0;

    protected:
        Info mInfo { };
    };

} // namespace sys
} // namespace dst
