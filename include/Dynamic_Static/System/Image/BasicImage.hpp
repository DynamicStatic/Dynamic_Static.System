
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
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
namespace detail {

    /*!
    TODO : Documentation
    */
    template <typename CRT>
    class BasicImage
    {
    public:
        /*!
        TODO : Documentation
        */
        struct Info
        {
            Format format { Format::Unknown }; //!< TODO : Documentation
            int width { 1 };                   //!< TODO : Documentation
            int height { 1 };                  //!< TODO : Documentation
        };

    public:
        /*!
        TODO : Documentation
        */
        inline BasicImage()
        {
            clear();
        }

        /*!
        TODO : Documentation
        */
        virtual ~BasicImage() = 0;

    public:
        /*!
        TODO : Documentation
        */
        inline const Info& get_info() const
        {
            return mInfo;
        }

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline Span<const PixelType> get_pixels() const
        {
            auto count = size_bytes() / sizeof(PixelType);
            return Span<PixelType>(reinterpret_cast<PixelType*>(data()), count);
        }

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline Span<PixelType> get_pixels()
        {
            auto count = size_bytes() / sizeof(PixelType);
            return Span<PixelType>(reinterpret_cast<PixelType*>(data()), count);
        }

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline const PixelType& get_pixel(glm::ivec2 uv) const
        {
            uv.x = std::clamp(uv.x, 0, mInfo.width - 1);
            uv.y = std::clamp(uv.y, 0, mInfo.height - 1);
            return get_pixels<const PixelType>()[uv.y * mInfo.width + uv.x];
        }

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline PixelType& get_pixel(glm::ivec2 uv)
        {
            uv.x = std::clamp(uv.x, 0, mInfo.width - 1);
            uv.y = std::clamp(uv.y, 0, mInfo.height - 1);
            return get_pixels<PixelType>()[uv.y * mInfo.width + uv.x];
        }

        /*!
        TODO : Documentation
        */
        inline size_t size_bytes() const
        {
            auto bpp = get_format_bytes_per_pixel(mInfo.format);
            return mInfo.width * mInfo.height * bpp;
        }

        /*!
        TODO : Documentation
        */
        virtual void clear()
        {
            mInfo.format = Format::Unknown;
            mInfo.width = 0;
            mInfo.height = 0;
        }

    private:
        const uint8_t* data() const
        {
            return static_cast<const CRT*>(this)->data();
        }

        uint8_t* data()
        {
            return static_cast<CRT*>(this)->data();
        }

    protected:
        Info mInfo { };
    };

    template <typename CRT>
    inline BasicImage<CRT>::~BasicImage()
    {
    }

} // namespace detail
} // namespace sys
} // namespace dst
