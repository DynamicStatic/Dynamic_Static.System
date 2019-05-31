
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Image/Image.hpp"

#include <type_traits>

namespace dst {
namespace sys {

    /*!
    Provides high level control over unmanaged image data
    */
    template <typename DataType = uint8_t>
    class UnmanagedImage final
        : public BasicImage
    {
    public:
        /*!
        Constructs an instance of UnmanagedImage
        */
        UnmanagedImage() = default;

        /*!
        Constructs an instance of UnmanagedImage
        @param [in] info This UnmanagedImage's Image::Info
        @param [in] data A pointer to the data to access via this UnmanagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        \n NOTE : If data is null this UnmanagedImage will be cleared
        */
        UnmanagedImage(
            const Info& info,
            DataType* data
        )
        {
            assign(info, data);
        }

        /*!
        Constructs an instance of UnmanagedImage
        @param [in] other The UnmanagedImage to copy from
        */
        inline UnmanagedImage(const UnmanagedImage& other)
        {
            *this = other;
        }

        /*!
        Constructs an instance of UnmanagedImage
        @param [in] other The UnmanagedImage to copy from
        @return This UnmanagedImage after being copied to
        */
        inline UnmanagedImage& operator=(const UnmanagedImage& other)
        {
            mData = other.mData;
            BasicImage::operator=(other);
        }

        /*!
        Moves an instance of UnmanagedImage
        @param [in] other The UnmanagedImage to move from
        */
        inline UnmanagedImage(UnmanagedImage&& other)
        {
            *this = std::move(other);
        }

        /*!
        Moves an instance of UnmanagedImage
        @param [in] other The UnmanagedImage to move from
        @return This UnmanagedImage after being moved to
        */
        inline UnmanagedImage& operator=(UnmanagedImage&& other)
        {
            mData = std::move(other.mData);
            BasicImage::operator=(std::move(other));
            return *this;
        }

    public:
        /*!
        Assigns an Image::Info and pixel data to this UnmanagedImage
        @param [in] info This UnmanagedImage's Image::Info
        @param [in] data A pointer to the data to access via this UnmanagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        \n NOTE : If data is null this UnmanagedImage will be cleared
        */
        inline void assign(
            const Info& info,
            DataType* data
        )
        {
            if (data) {
                mInfo = info;
                mData = data;
            } else {
                clear();
            }
        }

        /*!
        Gets this UnmanagedImage's pixel data
        @param <PixelType = uint8_t> The type to interpret this UnmanagedImage's pixel data as
        @return This UnmanagedImage's pixel data
        */
        template <typename PixelType = uint8_t>
        typename std::enable_if<std::is_const<DataType>::value, Span<const PixelType>>::type
        inline get_pixels() const
        {
            return BasicImage::get_pixels<PixelType>();
        }

        /*!
        Gets this UnmanagedImage's pixel data
        @param <PixelType = uint8_t> The type to interpret this UnmanagedImage's pixel data as
        @return This UnmanagedImage's pixel data
        */
        template <typename PixelType = uint8_t>
        typename std::enable_if<!std::is_const<DataType>::value, Span<PixelType>>::type
        inline get_pixels()
        {
            return { mData, size_bytes() / sizeof(PixelType) };
        }

        /*!
        Gets this UnmanagedImage's pixel at the given uv coordinate
        \n NOTE : uv coordinate (0, 0) returns the pixel at the top left corner of this UnmanagedImage
        @param <PixelType = uint8_t> The type to interpret this UnmanagedImage's pixel data as
        @param [in] uv The uv coordinate of the pixel to get
        */
        template <typename PixelType = uint8_t>
        typename std::enable_if<std::is_const<DataType>::value, const PixelType&>::type
        inline get_pixel(glm::ivec2 uv) const
        {
            return BasicImage::get_pixel<PixelType>(uv);
        }

        /*!
        Gets this UnmanagedImage's pixel at the given uv coordinate
        \n NOTE : uv coordinate (0, 0) returns the pixel at the top left corner of this UnmanagedImage
        @param <PixelType = uint8_t> The type to interpret this UnmanagedImage's pixel data as
        @param [in] uv The uv coordinate of the pixel to get
        */
        template <typename PixelType = uint8_t>
        typename std::enable_if<!std::is_const<DataType>::value, PixelType&>::type
        inline get_pixel(glm::ivec2 uv)
        {
            return const_cast<PixelType&>(BasicImage::get_pixel(uv));
        }

        /*!
        Clears this UnmanagedImage
        */
        inline void clear() override final
        {
            mData = nullptr;
            BasicImage::clear();
        }

    private:
        inline const uint8_t* data() const
        {
            return mData;
        }

        DataType* mData { nullptr };

        static_assert(
            std::is_same<DataType, uint8_t>::value ||
            std::is_same<DataType, const uint8_t>::value,
            "UnmanagedImage DataType must be uint8_t or const uint8_t"
        );
    };

} // namespace sys
} // namespace dst
